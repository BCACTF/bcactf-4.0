from Crypto.Util.number import *
given1 = b"I need to buy 15 eggs, 1.7 kiloliters of milk, 11000 candles, 12 cans of asbestos-free cereal, and 0.7 watermelons."
given2 = open("grocery-list.out", "rb").read()
flag_enc = open("many-time-pad.out", "rb").read()

def xor(a, b):
    return long_to_bytes(bytes_to_long(a) ^ bytes_to_long(b))

# a one-time pad is only secure if the key is actually used one time. here's a very simple example as to how it can go wrong
# you can easily recover the key from the given plaintext and ciphertext since xor is reversible
key = xor(given1, given2)
# now just win
print(xor(flag_enc, key))