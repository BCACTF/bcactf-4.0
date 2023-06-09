import { parse } from 'yaml'
import { readdirSync as readDirSync, readFileSync } from "fs";
import { join, dirname } from "path";

import { fileURLToPath } from 'url';
const __dirname = dirname(fileURLToPath(import.meta.url));

const files = readDirSync(join(__dirname, "..", ".."), {withFileTypes: true});

const challs = []

for (const f of files) {
    if (f.isDirectory() && !f.name.startsWith(".") && f.name !== "checker") {
        const chall = f.name;
        const path = join(__dirname, "..", "..", chall)
        const y = readFileSync(join(path, "./chall.yaml"), "utf-8");
	    const data = parse(y);
        challs.push({...data, dir: chall, path});
	}
}

export default challs;