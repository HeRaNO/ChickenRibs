m = 1926081719260817
M = m

def mul(a, b):
	n = len(a)
	p = len(a[0])
	assert(p == len(b))
	m = len(b[0])
	r = []
	for i in range(n):
		r.append([0 for j in range(m)])
	for i in range(n):
		for j in range(m):
			for k in range(p):
				r[i][j] += a[i][k] * b[k][j] % M
				r[i][j] %= M
	return r

def fpow(a, b):
	n = len(a)
	r = []
	for i in range(n):
		r.append([0 for j in range(n)])
		r[i][i] = 1
	while b != 0:
		if b & 1 == 1:
			r = mul(r, a)
		a = mul(a, a)
		b >>= 1
	return r

def F(n):
	a = [[1, 1], [1, 0]]
	r = fpow(a, n)
	return r[0][1]

flag = "cnss{" + hex(F(m))[2:] + "}"
print(flag)
