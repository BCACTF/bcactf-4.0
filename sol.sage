#!/usr/bin/env sage

from sage.all import *
from Crypto.Util.number import *

p = 0x23FFFFFDC000000D7FFFFFB8000001D3FFFFF942D000165E3FFF94870000D52FFFFDD0E00008DE55C00086520021E55BFFFFF51FFFF4EB800000004C80015ACDFFFFFFFFFFFFECE00000000000000067
K = GF(p)
a = K(0x0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000)
b = K(0x0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000101)
E = EllipticCurve(K, (a, b))
G = E(0x23FFFFFDC000000D7FFFFFB8000001D3FFFFF942D000165E3FFF94870000D52FFFFDD0E00008DE55C00086520021E55BFFFFF51FFFF4EB800000004C80015ACDFFFFFFFFFFFFECE00000000000000066, 0x0000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000010)
o = 0x23FFFFFDC000000D7FFFFFB8000001D3FFFFF942D000165E3FFF94870000D52FFFFDD0E00008DE55600086550021E555FFFFF54FFFF4EAC000000049800154D9FFFFFFFFFFFFEDA00000000000000061
E.set_order(o)

z1 = int.from_bytes(bytes("Hello world!", 'utf-8'), 'big')
z2 = int.from_bytes(bytes("The quick brown fox jumps over the lazy dog", 'utf-8'), 'big')
r = 394265082124615459155530563721344254643735610268730387434768649125969237030632747812974199346498872332826729866624662205276053883717679100648095904798281919234564985558723423304684224638102336
s1 = 613909209959882818732644911946233854167334105676497302633252322671805611475347114043493588995082759429640066981776822479054440264864232929215773070105835168226884512073853233614264678611112943
s2 = 543481719459711603697340629941246701353229291355413378408675683997766377647419805863247451456757806055040260918322994617774457863170968969137455903968181709931700665362031343080288361788043403
s3 = 238353596186904342726878869981624404566377276626701828108643282926988767695842081411879777456692702361198784768394606539663687724135458000640081796986143209867905104764889982684215287582758163

key2 = mod((z1-z2)/(s1-s2),o)
key = mod((s1*key2-z1)/r,o)

ans = s3 * key2 - r * key
print(long_to_bytes(int(ans)))