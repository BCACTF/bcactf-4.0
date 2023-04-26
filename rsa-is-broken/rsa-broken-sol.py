from Crypto.Util.number import *
import math
import re
p = 892582974910679288224965877067
q = 809674535888980601722190167357
c = 36750775360709769054416477187492778112181529855266342655304
n = p * q
e = 65537

# the idea is that our retrieved m is in fact equivalent to the original m mod n
# so we add multiples of n to retrieve the flag
# but this is inefficient so we have to narrow it down using format
# The flag ends with }, so 7D = 125 mod 256
d = pow(e, -1, math.lcm(p-1, q-1))
m = pow(c, d, n)
while m % 256 != 125:
    m += n
jump = n * 256
# the flag starts with bcactf{
# we essentially want to try one possible flag length at a time
# by jumping up to the next one starting with bcactf
# 0 is the smallest char (by code) that can appear in the flag
target = b'bcactf{' + b'0'*math.floor(math.log(m, 256)-7)
md = long_to_bytes(m)
while re.fullmatch(b'[0-9a-zA-Z_{}]+', md) == None:
    if md[0:7] == b'bcactf{':
        m += jump
        # print(md)
    else:
        m += jump * math.ceil((bytes_to_long(target) - m)/jump)
        target += b'0'
        # print(math.log(m,2))
    md = long_to_bytes(m)
print(md)
