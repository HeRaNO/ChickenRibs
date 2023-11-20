from base64 import b64decode
from Crypto.Util.number import long_to_bytes

secret1 = 30772543014919602267414633191
secret2 = 'bc96e7a081e698afe5ada620'
secret3 = '0b10000110111001001111001011100000111010001101111001000001110011110011010100001001110011110101100'
secret4 = b'rOS4gOatpeOAgiF9'

flag1 = long_to_bytes(secret1)
flag2 = long_to_bytes(int(secret2, 16))
flag3 = long_to_bytes(int(secret3, 2))
flag4 = b64decode(secret4)

flag = flag1 + flag2 + flag3 + flag4

print(flag.decode())

