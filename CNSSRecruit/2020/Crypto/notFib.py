from json import load

n = 2020
m = 1926081719260817
M = m
a = load(open("a", "r"))

assert(len(a) == n)
assert(all([1 < ai and ai < m for ai in a]))

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

def L(n):
	a = [[1, 1], [1, 0]]
	r = [[1], [2]]
	r = mul(fpow(a, n - 1), r)
	return r[0][0]

def P(n):
	if n & 1 == 1:
		return 1
	return M - 1

# F_a+F_{a+b}+F_{a+2b}+...+F_{a+nb}
def sumFib(n, a, b):
	A = [[L(b), P(b), 0], [1, 0, 0], [1, 0, 1]]
	r = [[F(a + b)], [F(a)], [F(a)]]
	r = mul(fpow(A, n), r)
	return r[2][0]

ans = 0
for ai in a:
	k = (m - 1) // ai
	f = m - k * ai
	assert((m - f) % ai == 0)
	n = (m - f) // ai - 1
	ans += sumFib(n, f, ai)
	ans %= M

ans = (ans + F(m)) % M

flag = "cnss{" + hex(ans)[2:] + "}"
print(flag)
