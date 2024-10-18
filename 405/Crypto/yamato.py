import time
import random
from Crypto.Util.number import *
from mt19937predictor import MT19937Predictor

msg = b''
with open('msg','rb') as f:
    msg = f.read()
print(len(msg) // 4)

c = b''
with open('ciphertext','rb') as f:
    c = f.read()
print(len(c) // 4)

predictor = MT19937Predictor()

for i in range(624):
    x = bytes_to_long(msg[i*4:i*4+4]) ^ bytes_to_long(c[i*4:i*4+4])
    predictor.setrandbits(x, 32)

i = 624
x = bytes_to_long(msg[i*4:i*4+4]) ^ bytes_to_long(c[i*4:i*4+4])

assert x == predictor.getrandbits(32)

flag = b''

for i in range(625, 635):
    x = bytes_to_long(c[i*4:i*4+4]) ^ predictor.getrandbits(32)
    flag += long_to_bytes(x)

print(flag)
