import express, { text } from "express";
import { readFileSync } from "fs";
import { spawn } from "child_process";

import { bufToBlock } from "../base/block";
import { build, fromBlocks } from "../base/repository";

import recievedBlocks from "../chall/gen";

const server = express();

const index = readFileSync("server/index.html", "utf-8");


server.use(text());

server.get(
    "/",
    async (_, res) => {
        res.send(index);
    }
);
server.post(
    "/submit",
    async (req, res) => {
        const body = req.body;
        if (typeof body !== "string") {
            res.status(400).send("Bad Body");
            return;
        }
        console.log("Submit req recieved with body:", body.slice(0, 1024));

        const buffer = Buffer.from(body);
        const block = bufToBlock(buffer);

        if (!block) {
            res.status(400).send("Malformed Block");
            return;
        }

        const repo = fromBlocks([
            bufToBlock(Buffer.from(recievedBlocks[0][1]))!,
            block,
            bufToBlock(Buffer.from(recievedBlocks[1][1]))!,
            bufToBlock(Buffer.from(recievedBlocks[2][1]))!,
        ]);

        const output = build(repo);
        if (!output) {
            res.status(400).send("Corruption or tampering detected...\n\nHOW DARE YOUUUUU..........");
            return;
        }

        const controller = spawn("deno", ["run", "--allow-read=./flag.txt", "-"]);
        
        controller.stdin.write(output.toString("ascii") + "\n");
        controller.stdin.end();
        
        controller.stderr.pipe(process.stderr, { end: false });

        res.write("Output:\n");
        controller.stdout.pipe(res);
    }
);


server.listen(8080, () => console.log("Listening on 8080"));
