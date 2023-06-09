from Crypto.Util.number import getPrime, bytes_to_long, long_to_bytes
from Crypto.Hash import SHA256
import random, string, binascii, re
# Example parameters
n = 333113690631843593172069657888161380880744003402171972441891697024879633913485392519615292338955215520098551595863650555912764232238187560021568544598423943252925882505288117881580939460888880974955205394754177269612425819036571469491992228568603185313316207697068324221937296992617338744758410515858643821121088761196689065501497328758114615924609150606362833468659088737979679920827002863570389816983693900054231312601341633989983296974402210578299867081897991752268521181462550259092109751054306682218905887969418225749366250842262751048119132522563583187560882748489561725960882820700010267726664636857066363283464427396788171472680701426188033305815382069740844582189350196216333462770659592151848260511457095805565308429425822484936208745392823288900694985414324329020429747732337289675640198888681511633709335456471093983396397873021656531376178004271264859710802740258766419816258209833731980169714482170357243831430999032236018785419062794130063040465009540258114701763793486249007928569428019954087881875103514585866347724869092545549337186033208716856424560077335892010910264553217722209018369265402708573887979076480864016868552375141829520199358408236475664883508300508829665109471405458989289346364116014469163852923479
t = b"i!QN5lH_^Jv3IVB27Re;"
h = SHA256.new()
h.update(t)
hash = h.digest()
# Solution based on https://mailarchive.ietf.org/arch/msg/openpgp/5rnE9ZRN1AokBVj3VqblGlP63QE/
inv = (1 << 264) - bytes_to_long(hash)
print(binascii.hexlify(long_to_bytes((1<<1019) - (inv * (1 << 34) // 3)))) # may be some edge cases where there is a rounding issue, but should beZ