BinaryRing = Integers(2)

def hasher(modulo, base, exp, idx):
    rawval = base ^ exp * idx
    modded_val = rawval % modulo
    bits = ("0" * 128 + bin(modded_val)[2:])[-128:]
    return [BinaryRing(int(bits[i])) for i in range(len(bits))]


def hasher_diff(modulo, base, exp1, exp2, idx):
    raw_val1 = base ^ exp1 * idx
    raw_val2 = base ^ exp2 * idx
    modded_val1 = raw_val1 % modulo
    modded_val2 = raw_val2 % modulo
    modded_val = modded_val1 ^^ modded_val2
    bits = ("0" * 128 + bin(modded_val)[2:])[-128:]
    return [BinaryRing(int(bits[i])) for i in range(len(bits))]





target = int(input("What's the target hash? "))
curr = int(input("What's the current hash? "))
start_idx = int(input("What index is the hex started at? "))
chr1 = input("What is the current character? ")
chr2 = input("What is the other options for the character? ")
modulo = int(input("What is the modulo? "))
power = int(input("What is the power? "))

char_1_hex = ("0" + hex(ord(chr1))[2:])[-2:]
char_2_hex = ("0" + hex(ord(chr2))[2:])[-2:]

char_1_high = ord(char_1_hex[0])
char_1_low = ord(char_1_hex[1])

char_2_high = ord(char_2_hex[0])
char_2_low = ord(char_2_hex[1])

row_generator = (
    hasher_diff(modulo, power, char_1_high, char_2_high, idx)
        if (idx - start_idx) % 2 == 0
        else hasher_diff(modulo, power, char_1_low, char_2_low, idx)
    for idx in range(start_idx, start_idx + 128)
)

hard_matrix = matrix(BinaryRing, list(row_generator)).transpose()

inverse = hard_matrix.inverse()

__target_hash_xor_str = bin(curr ^^ target)[2:]
target_hash_xor = ('0' * 128 + __target_hash_xor_str)[-128:]

curr_hash_as_matrix = matrix(BinaryRing, [BinaryRing(int(char)) for char in target_hash_xor]).transpose()
# print(curr_hash_as_matrix.str())

solution_matrix = inverse * curr_hash_as_matrix

# print(solution_matrix.str())

def get_chr(high, low):
    return chr(int(
        chr([char_1_high, char_2_high][high]) +
        chr([char_1_low, char_2_low][low]),
        16
    ))

solution_str = "".join(get_chr(high[0], low[0]) for (high, low) in zip(solution_matrix[::2], solution_matrix[1::2]))

print(f'add `ANSWER="{solution_str}"` to the beginning of `npm run solve`')
