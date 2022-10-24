from Crypto.Util.number import bytes_to_long, long_to_bytes

def highLow(x):
	return (x >> 32, x % (2 ** 32))

flag = b'cnss{I_a'
f0 = bytes_to_long(flag)
p = [4840951631397558164, 5492303526413306583, 6271460196030786735, 6127905759336302986, 601209385465514967]
MASK2 = 16500653344889503744
f1 = p[0]
hf0, lf0 = highLow(f0)
hf1, lf1 = highLow(f1)
hk = hf1 ^ lf0 ^ (MASK2 >> 32)
lk = lf1 ^ hf0
key = (hk << 32) + lk

flag = ''
for i in p:
	l, h = highLow(i ^ MASK2 ^ key)
	flag += long_to_bytes((h << 32) | l).decode()
print(flag)
