#!/usr/bin/env sage

from sage.all import *
from Crypto.Util.number import *

p = 0x23FFFFFDC000000D7FFFFFB8000001D3FFFFF942D000165E3FFF94870000D52FFFFDD0E00008DE55C00086520021E55BFFFFF51FFFF4EB800000004C80015ACDFFFFFFFFFFFFECE00000000000000067
K = GF(p)
a = K(0)
b = K(0x101)
E = EllipticCurve(K, (a, b))
G = E(p-1, 0x10)
o = 0x23FFFFFDC000000D7FFFFFB8000001D3FFFFF942D000165E3FFF94870000D52FFFFDD0E00008DE55600086550021E555FFFFF54FFFF4EAC000000049800154D9FFFFFFFFFFFFEDA00000000000000061
E.set_order(o)

# Googling for "elliptic curve signature" or similar should point you to
# https://en.wikipedia.org/wiki/Elliptic_Curve_Digital_Signature_Algorithm
# the p, K, a, b, E, g, o stuff is just selecting the elliptic curve used
# As the Wikipedia page notes, "k" must be random, but investigating the
# challenge shows that the "k" used is actually key1 from secrets.py.
# In addition, the flag was not hashed before signing, which allows us
# to recover it if we figure out the private key.
# Here we do exactly as described on Wikipedia:

# data from signature-ii-log.txt
z1 = int.from_bytes(bytes("Hello world!", 'utf-8'), 'big')
z2 = int.from_bytes(bytes("The quick brown fox jumps over the lazy dog", 'utf-8'), 'big')
# note how since all "k"s were the same, so are all "r"s
r = 394265082124615459155530563721344254643735610268730387434768649125969237030632747812974199346498872332826729866624662205276053883717679100648095904798281919234564985558723423304684224638102336
s1 = 613909209959882818732644911946233854167334105676497302633252322671805611475347114043493588995082759429640066981776822479054440264864232929215773070105835168226884512073853233614264678611112943
s2 = 543481719459711603697340629941246701353229291355413378408675683997766377647419805863247451456757806055040260918322994617774457863170968969137455903968181709931700665362031343080288361788043403
s3 = 238353596186904342726878869981624404566377276626701828108643282926988767695842081411879777456692702361198784768394606539663687724135458000640081796986143209867905104764889982684215287582758163

key1 = mod((z1-z2)/(s1-s2),o) # k = (z-z')/(s-s')
key2 = mod((s1*key1-z1)/r,o) # private key dA = (sk-z)/r

# now with both keys, we know s = k^-1(z+rdA)
# and just need to solve for z.
# sk = z + rdA, so z = sk - rdA
ans = s3 * key1 - r * key2
print(long_to_bytes(int(ans)))