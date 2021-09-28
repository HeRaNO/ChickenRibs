from Crypto.Util.number import long_to_bytes
from hashlib import md5

m = [312609034968489560095816917649428218927, 201093538614623911247134492490252725577, 298359341518180165381217901632470444187, 283779784104916354790175596793270218363]
a = [135563869850958998185249517440045295817, 78188242776496129424059232264784298435, 120640187605672057179209488273239034888, 75233765181335440789936728233620033742]

def exgcd(a,b):
	if b==0:
		return a, 1, 0
	res, x, y = exgcd(b, a % b)
	t = x
	x = y
	y = t - (a // b) * y
	return res, x, y

def exCRT(n):
	M = m[0]
	ans = a[0]
	for i in range(1, n):
		g, x, y = exgcd(M, m[i])
		if (a[i] - ans) % g != 0:
			return -1
		x = (a[i] - ans) // g * x % (m[i] // g)
		ans = ans + x * M
		M = M // g * m[i]
		ans %= M
	ans = (ans + M) % M
	if ans == 1:
		return ans + M
	return ans

flag = "cnss{" + md5(long_to_bytes(exCRT(4))).hexdigest() + "}"
print(flag)
