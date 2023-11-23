from sage.all import *
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad
from Crypto.Util.number import long_to_bytes

def decrypt(data, key):
    cipher = AES.new(key, AES.MODE_ECB)
    return unpad(cipher.decrypt(data), AES.block_size).decode()

p = 9348030992978262347982920431034912130716881552084115381757548130699185130820479730646974634141092089651314678852571714802122984104452942803209295252010181
a = 7763518046982192251231517150944105482004832971680748456996310159078009542876654956303764776823623497403884988108392624824526960061132573798331838835960909
b = 10997613169313236085705837600762108982163011398922795151006166411501358991822489779966644769325114384948484844491824976044124478063235526767931678399125511
E = EllipticCurve(GF(p), [a, b])
e = 65537
Q = (702269728158503157149596097443623465665001736303612719716566418594125500303838352102906729735173073066319779069987350585597471722439620961396365725087358, 7741251535874845030195254089473397439416170375681731646623904995909698213716045714883145323049811857989495704699439881764120694648581710750825272993480662)
enc = b'c\xea\x0eO\xf1V\n"\xf4\xd5V\x10\x06\x85\xd8a\xe5`\xab\xd4\x9b\x96Fz+:\x0b\xaeg-\x92\xe6\xfb:\xc7\xaf\x1b<\x04\xf0\x81\xb8\xbf\xc6\x96\x16q\x17\xd0\xb4F\x92L]\xa4\xe9|\xe1\xafg?\x1c\x88u{\x91\xe5=\x0c\xdb\xb6S\x02\xdd4\x90F.\xe8\xa9'

Q = E.point(Q)
d = inverse_mod(e, E.order())
P = d * Q
x = P[0]
# x = 229350946853232837168900659503406426315

print(decrypt(enc, long_to_bytes(x)))