import { WebSocketServer } from 'ws';
import * as game from './server/game.js';
import * as http from 'http';
import * as fs from 'fs';
const PORT = 3000;

const indexHTML = fs.readFileSync("./public/index.html", 'utf-8');
const jsCode = fs.readFileSync("./public/wasm.js", "utf-8");
const wasmCode = fs.readFileSync("./public/wasm.wasm");
const images = [
    "clubpenguin.png",
    "pop.png",
    "sonny.png",
    "ggfl44gs.png",
    "profesor.png",
    "nose.png",
    "r3lax.png"
].map(e => ({path:e, img: fs.readFileSync('./img/' + e)}));

const server = http.createServer((req, res) => {
    if (req.url === "/" || req.url === "/index.html") {
        res.writeHead(200, {
            'Content-Type': 'text/html',
        });
        res.write(indexHTML);
        res.end();
    } else if (req.url === "/wasm.js") {
        res.writeHead(200, {
            'Content-Type': 'text/javascript',
        });
        res.write(jsCode);
        res.end();
    } else if (req.url === "/wasm.wasm") {
        res.writeHead(200, {
            'Content-Type': 'application/wasm',
        });
        res.write(wasmCode);
        res.end();
    } else {
        for (const {path, img} of images) {
            if (req.url.split('/').at(-1) === path) {
                res.writeHead(200, {
                    'Content-Type': 'image/png',
                });
                res.write(img);
                res.end();
                return;
            }
        }

        res.writeHead(404, "Not found")
        res.end();
    }
});

const wss = new WebSocketServer({
    maxPayload: 256, // change if adding captcha
    path: '/super',
    server
});

wss.on("connection", game.client)

server.listen(PORT, "0.0.0.0", () => {
    console.log(`Listening on port ${PORT} at ${server.address().address || server.address()}`);
});