from sage.all import *
from Crypto.Cipher import AES
from Crypto.Util.Padding import unpad

p = 203941811645138463830158560032330799163
enc = '6e616b5196be0776299c4c7250c52e74810de07f7d74108b64b83a68c86f226e5930bcc500963d374678d5d63f6dd4d8'
enc = bytes.fromhex(enc)
P = (1, 3)
Q = (21390005523651821820907389545534742880, 192274032931065823063473687218912640869)

alpha = GF(p)(p - 2).square_root()
P_ = (P[0] + 2, P[1])
Q_ = (Q[0] + 2, Q[1])
def map_to_GF(P):
	x, y = P
	return (y + alpha * x) / (y - alpha * x)

u = map_to_GF(P_)
v = map_to_GF(Q_)
k = v.log(u)
d = multiplicative_order(u)

for i in range(p - k // d):
	key = int(k + i * d)
	cipher = AES.new(key.to_bytes(16, 'big'), AES.MODE_CBC, bytes(16))
	try:
		plaintext = unpad(cipher.decrypt(enc), 16).decode()
	except Exception as e:
		continue
	else:
		print(plaintext)
		break
