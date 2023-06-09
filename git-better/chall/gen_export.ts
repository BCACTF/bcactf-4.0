import recievedBlocks from "./gen";

let output = "[\n\t";

for (const block of recievedBlocks) {
    output += '[\n\t\t0x';
    output += block[0].toString(16);
    output += 'n,\n\t\t';
    output += JSON.stringify(block[1]);
    output += '\n\t],\n\t';
}
output = output.slice(0, -1) + ']';

console.log(output);
