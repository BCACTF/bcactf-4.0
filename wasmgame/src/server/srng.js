import {readFileSync} from "fs";
import { dirname, join } from "path";
import { fileURLToPath } from 'url';


const __dirname = dirname(fileURLToPath(import.meta.url));

export default await WebAssembly.instantiate(readFileSync(join(__dirname, "./a.out.wasm"))).then(wasm => ({
    srand: wasm.instance.exports.srand,
    rand: wasm.instance.exports.rand
})).catch(e => console.error(e))