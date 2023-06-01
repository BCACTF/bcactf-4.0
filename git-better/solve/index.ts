import recievedBlocks, { lostBlock } from "../chall/gen";
import { Block, blockToBuf, bufToBlock } from "../base/block";
import myHashFunction, { powerPrime, modPrime } from "../base/hashing";
import { appended, build, fromBlocks, newRepo } from "../base/repository";

if (process.env.DIFFICULTY?.toLowerCase() === "hard") {
    // 
    const char1 = "f";
    const char2 = "x";

    const fill = process.env.ANSWER ? process.env.ANSWER : char1.repeat(64);

    // console.log({ using: fill });

    const targetHash = myHashFunction(Buffer.from(lostBlock));
    const buffer = Uint8Array.from(Buffer.from("\n--MANIP--\n" + `${fill}*/\nconsole.log(fileData);`));
    
    let replacementBlock: Block = {
        prevHash: recievedBlocks[0][0],
        changes: [
            { index: 122, remove: 0, insert: Uint8Array.from(Buffer.from("\\}")) },
            { index: 126, remove: 0, insert: Uint8Array.from(Buffer.from("/*")) },
            { index: 71, remove: 0, insert: Uint8Array.from(Buffer.from("// Fixed the mismatched bracket issue.\n")) },
            { index: 244, remove: 0, insert: buffer },
        ],
    };

    // console.log(blockToBuf(replacementBlock).toString("ascii"));

    const alteredHash = myHashFunction(blockToBuf(replacementBlock));

    
    const chars = ("00" + char1.charCodeAt(0).toString(16)).slice(-2).repeat(64);
    
    console.log("targ:", targetHash);
    console.log("curr:", alteredHash);
    console.log("strt:", blockToBuf(replacementBlock).indexOf(chars));
    console.log("chrs:", char1, char2);
    console.log("modu:", modPrime);
    console.log("powr:", powerPrime);


    if (targetHash === alteredHash) {
        const repo = fromBlocks([
            bufToBlock(Buffer.from(recievedBlocks[0][1]))!,
            replacementBlock,
            bufToBlock(Buffer.from(recievedBlocks[1][1]))!,
            bufToBlock(Buffer.from(recievedBlocks[2][1]))!,
        ]);
        console.log(build(repo)?.toString("ascii"));

        console.log(blockToBuf(replacementBlock).toString("ascii"));
        // eval(build(repo)!.toString("ascii"))
    } else console.log("enter the above data to solve.sage");
} else {
    const buffer = Uint8Array.from(Buffer.from("\n--MANIP--\n" + `${"0".repeat(10)}*/\nconsole.log(fileData);`));

    const setBuf = (newVal: bigint) => buffer.set(Buffer.from(newVal.toString(36).padStart(10, "0")), 11);

    const targetHash = myHashFunction(Buffer.from(lostBlock));
    
    let replacementBlock: Block = {
        prevHash: recievedBlocks[0][0],
        changes: [
            { index: 122, remove: 0, insert: Uint8Array.from(Buffer.from("\\}")) },
            { index: 126, remove: 0, insert: Uint8Array.from(Buffer.from("/*")) },
            { index: 71, remove: 0, insert: Uint8Array.from(Buffer.from("// Fixed the mismatched bracket issue.\n")) },
            { index: 244, remove: 0, insert: buffer },
        ],
    };

    let currNum = 0n;

    while (myHashFunction(blockToBuf(replacementBlock)) !== targetHash) {
        // if (currNum % 1000n === 0n) console.log(myHashFunction(blockToBuf(replacementBlock)));

        setBuf(++currNum);
    }


    const modifiedRepo = appended(
        appended(
            appended(
                appended(
                    newRepo(),
                    bufToBlock(Buffer.from(recievedBlocks[0][1]))!.changes
                ),
                replacementBlock.changes
            ),
            bufToBlock(Buffer.from(recievedBlocks[1][1]))!.changes
        ),
        bufToBlock(Buffer.from(recievedBlocks[2][1]))!.changes
    );

    const origRepo = appended(
        appended(
            appended(
                appended(
                    newRepo(),
                    bufToBlock(Buffer.from(recievedBlocks[0][1]))!.changes
                ),
                bufToBlock(Buffer.from(lostBlock))!.changes
            ),
            bufToBlock(Buffer.from(recievedBlocks[1][1]))!.changes
        ),
        bufToBlock(Buffer.from(recievedBlocks[2][1]))!.changes
    );

    console.log(`Manipulation value: ${currNum.toString(36).padStart(10, '0')}`);
    console.log();
    console.log("original output:");

    // eval(build(origRepo)!.toString("ascii"));

    console.log();
    console.log("modified output:");
    
    // eval(build(modifiedRepo)!.toString("ascii"));

    const target = Buffer.from(Buffer.from(currNum.toString(36)).toString("hex"));
    const blockBuf = blockToBuf(replacementBlock);
    console.log(target.toString());
    console.log(blockBuf.toString());
    console.log(blockBuf.indexOf(target));
}
