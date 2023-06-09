import wasm from "./srng.js";

export const qcrypt = () => {
    return {
        decrypt(ws, bytes) {
            wasm.srand(ws.seed);
            wasm.rand();
            for (let i = 0; i < bytes.length; ++i) {
                bytes[i] ^= wasm.rand();
            }
            for (let i = 0; i < bytes.length; ++i) ws.seed = (ws.seed + bytes[i]) | 0;

            return bytes;
        },
        encrypt(ws, bytes) {
            wasm.srand(ws.seed2);
            wasm.rand();
            for (let i = 0; i < bytes.length; ++i) ws.seed2 = (ws.seed2 + bytes[i] + 7) | 0;
            for (let i = 0; i < bytes.length; ++i) {
                bytes[i] ^= wasm.rand();
            }

            return bytes;
        }
    }
}