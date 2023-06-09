export let modPrime = (2n ** 128n - 159n); // MOD_PRIME
export let powerPrime = 0xd30a1674117779a3n; // POWER_PRIME

export const setSpecialPrime = (n: bigint) => modPrime = n;
export const setPowerPrime = (n: bigint) => powerPrime = n;


const myHashFunction = (data: Buffer) => {
    let currentHash: bigint = 0n;

    for (let i = 0n; i < data.byteLength; i++) {
        const byte = data[Number(i)];

        currentHash ^= (powerPrime ** BigInt(byte) * i) % modPrime;
    }

    return currentHash;
};

export default myHashFunction;
