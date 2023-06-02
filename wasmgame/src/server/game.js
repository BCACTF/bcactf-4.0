import WebSocket from 'ws';
import { qReader, qWriter } from './bin.js';
import definitions from "./definition.js";
import { qcrypt } from './crypt.js';

const MAX_SPEED = 40;
const MAPR = 1024;
const FRICTION = -0.2;
const DEFAULT_BALL_RADIUS = 128;
const balls = [];
const hhh = new Set();
balls.remove = (obj) => {
    let i = balls.indexOf(obj);
    if (i === -1) return;
    if (i === balls.length - 1) balls.pop();
    else balls[i] = balls.pop();
}
class Ball {
    constructor(ws) {
        balls.push(this)
        this.id = Math.floor(Math.random() * 0xFFFFFFFF)
        this.ws = ws;
        this.lvx = 0;
        this.lvy = 0;
        this.vx = 0;
        this.vy = 0;
        this.x = 0;
        this.y = 0;
        this.r = DEFAULT_BALL_RADIUS;
        this.skin = 0;
        this.rot = 0;
    }

    tick() {
        // apply vx
        this.vx += this.lvx;
        this.vy += this.lvy;
        this.x += this.vx;
        this.y += this.vy;
        this.vx += this.vx * FRICTION;
        this.vy += this.vy * FRICTION;
        this.rot += (((this.vx ** 2) + (this.vy ** 2)) / MAX_SPEED) * 0.004;
        this.rot = (this.rot) % (Math.PI * 2);
        this.r = (((((this.lvx ** 2) + (this.lvy ** 2)) / MAX_SPEED) * 0.1) + 0.75) * DEFAULT_BALL_RADIUS;
        this.lvx = this.lvy = 0;

        // stay in bounds
        if ((this.x ** 2) + (this.y ** 2) > (MAPR - this.r) ** 2) {
            const ang = Math.atan2(this.y, this.x);
            this.x = Math.cos(ang) * (MAPR - this.r);
            this.y = Math.sin(ang) * (MAPR - this.r);
        }
    }

    destroy() {
        balls.remove(this);
    }

    writeTo(w) {
        w.vu32(this.id);
        w.f32(this.x);
        w.f32(this.y);
        w.f32(this.rot);
        w.vu32(this.r);
        w.vu32(this.skin)
    }

    sendWith10OtherBalls() {
        const w = qWriter().vu32(this.ws.ops.update);
        const cnt = Math.min(10, balls.length - 1);
        w.vu32(cnt + 1);
        this.writeTo(w);
        for (let i = 0, j = 0; i < cnt; j++) {
            if (balls[j] === this) continue;

            balls[j].writeTo(w);
            i += 1;
        }

        this.ws.talk(w.buf());
    }
}

setInterval(() => {
    if (balls.length) {
        for (const b of balls) b.tick();
        for (let i = 0; i < balls.length; ++i) {
            const b = balls[i];
            if (!b.ws || b.ws.readyState !== WebSocket.OPEN) {
                b.destroy();
                i -= 1;
                continue;
            }

            b.sendWith10OtherBalls();
        }
    }

    for (const w of hhh) {
        if (w.ponghim) {
            w.talk(qWriter()
                .vu32(w.ops.ping)
                .vu32(w.rng()).vu32(w.rng()).vu32(w.rng()).vu32(w.rng())
                .vu32(w.rng()).vu32(w.rng()).vu32(w.rng()).vu32(w.rng())
                .buf());
            w.ponghim  = false;
        }
    }
}, 100);

export const handshake = (ws) => {
    ws.talk(qWriter()
                .vu32(ws.ops.cookie)
                .vu32(ws.SEED)
                .buf())
    ws.talk(qWriter()
            .vu32(ws.ops.ping)
            .vu32(ws.rng()).vu32(ws.rng()).vu32(ws.rng()).vu32(ws.rng())
            .vu32(ws.rng()).vu32(ws.rng()).vu32(ws.rng()).vu32(ws.rng())
            .buf())

    let state = 10;

    ws.onmsg = (msg) => {
        if (ws.readyState !== WebSocket.OPEN) return;

        const r = qReader(msg);

        if (state >= 0) {
            if (r.vu32() !== ws.ops.ping) return ws.terminate();
            for (let i = 0; i < 8; ++i) {
                if (ws.rng() !== r.vu32()) return ws.terminate();
            }

            state -= 1;
            ws.ponghim = true;
        } else {
            ws.onmsg = null;
            texture(ws);
            ws.onmsg(msg);
        }
    }
}

export const texture = (ws) => {
    const w = qWriter(1024);
    w.vu32(ws.ops.texture);
    w.vu32(definitions.length);
    for (let i = 0; i < definitions.length; ++i) {
        const def = definitions[i];
        w.vu32(def.path.length);
        for (let j = 0; j < def.path.length; ++j) w.vu32(def.path.charCodeAt(j));
        w.vu32(def.hidden);
        w.vu32(def.name.length);
        for (let j = 0; j < def.name.length; ++j) w.vu32(def.name.charCodeAt(j));
    }

    ws.talk(w.buf());

    game(ws);
}

export const game = (ws) => {
    ws.onmsg = (msg) => {
        const r = qReader(msg);
        const op = r.vu32();

        if (op === ws.ops.ping) {
            for (let i = 0; i < 8; ++i) {
                if (r.vu32() !== ws.rng()) return ws.terminate();
            }

            ws.ponghim = true;

        }
        if (op !== ws.ops.update) return;

        let tx = r.f32();
        const skin = r.vu32();
        let ty = r.f32();

        if (!isFinite(tx)) tx = 0;
        if (!isFinite(ty)) ty = 0;
        if (skin >= definitions.length) skin = 0;

        if (!ws.ball) ws.ball = new Ball(ws);

        ws.ball.skin = skin;
        let mag = Math.min(Math.max(Math.sqrt((tx ** 2) + (ty ** 2)), -MAPR), MAPR);
        const ang = Math.atan2(ty, tx);
        tx = Math.cos(ang) * mag;
        ty = Math.sin(ang) * mag;

        const vang = Math.atan2(ty - ws.ball.y, tx - ws.ball.x);
        const vmag = Math.min(Math.max(Math.pow(((ty - ws.ball.y) ** 2) + ((tx - ws.ball.x) ** 2), 0.2) * 2, 0), MAX_SPEED);
        ws.ball.lvx = Math.cos(vang) * vmag;
        ws.ball.lvy = Math.sin(vang) * vmag;
        // ws.ball.x = tx;
        // ws.ball.y = ty;
    }
}


export const client = (ws) => {
    hhh.add(ws);
    ws.binaryType = 'arraybuffer';
    ws.crypt = qcrypt();
    ws.talk = (bytes) => {
        if (ws.readyState === WebSocket.OPEN) {
            ws.send(ws.crypt.encrypt(new Uint8Array(bytes)))
        }
    }
    const SEED = BigInt(ws.SEED = Math.floor(Math.random() * 0x7FFFFFFF));
    const rng = ws.rng = (() => {
        let seed = SEED;
        const MOD = 0x7fffffffn;
        const MUL = 16807n;
        const INC = 0x998n + (SEED % 0x293n);

        return () => {
            let j = Number(seed = (seed * MUL + INC) % MOD);
            return j;
        }
    })();
    
    const rngf = ws.rngf = () => (rng() / 0x7fffffff);
    
    const _genop = (() => {
        const OPCODE_MAX = 182931;
        let ops = new Set();
    
        return () => {
            let o = Math.floor(rngf() * OPCODE_MAX);
            while (ops.has(o)) o = Math.floor(rngf() * OPCODE_MAX);
            ops.add(o);
            return o;
        }
    })();
    
    ws.ops = {
        cookie: _genop(),
        texture: _genop(),
        ping: _genop(),
        update: _genop(),
    }


    ws.onmsg = null;
    ws.on('error', () => ws.terminate());
    ws.on('close', () => {
        if (ws.ball) {
            ws.ball.destroy();
            ws.ball = null;
        }
        hhh.delete(ws);
        ws.terminate()
    });
    ws.on('message', (data) => {
        if (ws.onmsg) ws.onmsg(ws.crypt.decrypt(new Uint8Array(data)));
    })

    handshake(ws)
    
}