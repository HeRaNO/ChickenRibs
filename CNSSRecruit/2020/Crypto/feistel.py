import os

real_flag = 'cnss{....}'
fake_flag = 'cnss{c91cac1ae8106c3aa80d49bf60f1c8d8}'

def xor(a, b):
	return ''.join(chr(ord(x) ^ ord(y)) for (x, y) in zip(a, b))

def str_to_hex(s):
    return s.encode().hex()

def swap(a):
    return a[16: ] + a[ :16]

def single(m, k):
	assert len(m) == 32
	l = m[: 16]
	r = m[16: ]
	nl, nr = r, xor(k, xor(l, r))
	return nl + nr

def encrypt(m, k):
	for i in k:
		m = single(m, i)
	return swap(m)

k = []
for i in range(0, 16):
	k.append(os.urandom(8).hex())

l = ['l']
r = ['r']

def getXor(k, l, r):
	for x in r:
		if x in l:
			l.remove(x)
		else:
			l.append(x)
	l.append(k)
	return l
'''
for i in range(0, 16):
	_k = 'k' + str(i)
	nl, nr = r, getXor(_k, l, r)
	l, r = nl, nr
	print(l, r)
'''
def hex_to_str(s):
    return ''.join([chr(i) for i in [int(b, 16) for b in s.split(' ')]])

f = '64 64 68 6f 66 62 66 39 30 36 68 30 3a 61 3f 69 37 64 6d 69 6c 36 35 6d 36 64 35 6d 30 30 34 63'
y = bytearray.fromhex(f)
z = hex_to_str(f)

ori = 'c91cac1ae8106c3aa80d49bf60f1c8d8'
key1 = xor(z[16:], ori[16:])
key2 = xor(xor(ori[16:], ori[:16]), z[:16])

x = '53 5f 3d 6f 34 24 06 07 30 25 10 20 3a 3d 68 32 25 03 38 3f 2b 76 08 6d 30 26 0c 25 63 7d 0f 68'
z = hex_to_str(x)
r = xor(z[16:], key1)
l = xor(xor(z[:16], key2), r)
print(l + r)
