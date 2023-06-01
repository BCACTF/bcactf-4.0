import { Change } from "../base/block";
import { setPowerPrime, setSpecialPrime } from "../base/hashing";
import { appended, blocks, build, newRepo } from "../base/repository";

const V0 = `
const filePath = "./flag.txt";
const fileData = "bcactf{temp_flag}";

const flagValidatorRegex = /bcactf\\{[a-zA-Z0-9_\\-]+/;

if (!fileData.trim().match(flagValidatorRegex)) console.log("bad flag :(");
`;

const V1 = `
const filePath = "./flag.txt";
const fileData = "bcactf{temp_flag}";

// Fixed the mismatched bracket issue.
const flagValidatorRegex = /bcactf\\{[a-zA-Z0-9_-]+\\}/;

if (!fileData.trim().match(flagValidatorRegex)) console.log("bad flag :(");
`;

const V2 = `
import {readFileSync as readFile} from 'node:fs';

const filePath = "./flag.txt";
// Actually read the flag file.
const fileData = readFile(filePath, "utf8");

// Fixed the mismatched bracket issue.
const flagValidatorRegex = /bcactf\\{[a-zA-Z0-9_-]+\\}/;

if (!fileData.trim().match(flagValidatorRegex)) console.log("bad flag :(");
`;

const V3 = `
import {readFileSync as readFile} from 'node:fs';

const filePath = "./flag.txt";
// Actually read the flag file.
const fileData = readFile(filePath, "utf8");

// Fixed the mismatched bracket issue.
const flagValidatorRegex = /bcactf\\{[a-zA-Z0-9_\\-]+\\}/;

if (fileData.trim().match(flagValidatorRegex)) {
    console.log("Flag Matches");
} else {
    console.log("Flag does NOT match :(");
    console.log("Flag:", fileData);
}
`;

const V0_CHANGES: Change[] = [
    { index: 0, remove: 0, insert: Uint8Array.from(Buffer.from(V0)) },
];

const V1_CHANGES: Change[] = [
    { index: 122, remove: 0, insert: Uint8Array.from(Buffer.from("\\}")) },
    { index: 71, remove: 0, insert: Uint8Array.from(Buffer.from("// Fixed the mismatched bracket issue.\n")) }
];

const V2_CHANGES: Change[] = [
    { index: 1, remove: 0, insert: Uint8Array.from(Buffer.from("import {readFileSync as readFile} from 'node:fs';\n\n")) },
    { index: 83, remove: 0, insert: Uint8Array.from(Buffer.from("// Actually read the flag file.\n")) },
    { index: 132, remove: 19, insert: Uint8Array.from(Buffer.from("readFile(filePath, \"utf8\")")) },
];

const ELSE_STMT = `{
    console.log("Flag Matches");
} else {
    console.log("Flag does NOT match :(");
    console.log("Flag:", fileData);
}`;

const V3_CHANGES: Change[] = [
    { index: 261, remove: 1, insert: Uint8Array.from(Buffer.from("")) },
    { index: 304, remove: 28, insert: Uint8Array.from(Buffer.from(ELSE_STMT)) }
];

if (!process.env.USE_PRESETS) {
    if (process.env.DIFFICULTY?.toLowerCase() === "hard") {
        setSpecialPrime(0xffffffffffffffffffffffffffffff61n);
        setPowerPrime(0xd30a1674117779a3n);
    } else {
        setSpecialPrime(261557n);
        setPowerPrime(1933n);
    }
}

export const repo = appended(appended(appended(appended(newRepo(), V0_CHANGES), V1_CHANGES), V2_CHANGES), V3_CHANGES);

// console.log(repo);

const repoString = build(repo)?.toString("utf-8");
if (repoString !== "" && !repoString) throw new Error("Malformed repo!");

// console.log(repoString.trim() === V3.trim());

const recievedBlocksOrUndef = blocks(repo)?.filter((b, i) => i !== 1);
if (!recievedBlocksOrUndef) throw new Error("Malformed Repo");

const recievedBlocks = recievedBlocksOrUndef;
export default recievedBlocks;


const lostBlockOrUndef = blocks(repo)?.[1][1];
if (!lostBlockOrUndef) throw new Error("Malformed Repo");
export const lostBlock = lostBlockOrUndef;

if (process.env.PRINT_REPO) {
    console.log(repo);
    console.log(build(repo)?.toString("ascii"));
    console.log(lostBlock);
    console.log(recievedBlocks);
}
