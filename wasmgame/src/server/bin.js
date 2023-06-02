const u = new Uint8Array(4);
const f = new Float32Array(u.buffer);

export const qReader = (data) => {
    const bytes = new Uint8Array(new Uint8Array(data));
    let pos = 0;

    const oob = (inc=0) => (pos + inc) >= bytes.length;
    return {
        oob,
        vu32() {
            if (oob()) return 0;
            let out = bytes[pos] & 0x7F;
            let i = 0;
            while (bytes[pos++] & 0x80) {
                if (oob()) return 0;
                out |= (bytes[pos] & 0x7F) << (i += 7);
    
                if (i > 32) break;
            }

            return out;
        },
        f32() {
            if (oob(3)) return 0.0;

            u.set(bytes.subarray(pos, pos += 4), 0);

            return f[0];
        }
    }
}


export const qWriter = (MAX=512) => {
    const bytes = new Uint8Array(MAX);
    let pos = 0;
    const oob = (inc=0) => (pos + inc) >= bytes.length;
    return {
        oob,
        vu32(num) {
            do {
                if (oob()) break;
                bytes[pos] = num & 0x7F;
                num >>>= 7;
                if (num) bytes[pos] |= 0x80;
                pos += 1;
            } while (num > 0);

            return this;
        },
        f32(num) {
            if (oob(3)) return;

            f[0] = num;
            bytes.set(u, pos);
            pos += 4;

            return this;
        },
        buf() {
            return bytes.slice(0, pos);
        }
    }
}