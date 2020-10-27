def fpow(a, b, p):
	r = 1
	while b != 0:
		if b & 1 == 1:
			r = r * a % p
		a = a * a % p
		b >>= 1
	return r

def msqrt(n, p):
	if n == 0:
		return 0
	q = p - 1
	s = 0
	z = 2
	while ~q & 1 != 0:
		q >>= 1
		s += 1
	if s == 1:
		return fpow(n, (p + 1) // 4, p)
	while fpow(z, (p - 1) // 2, p) == 1:
		z += 1
	c = fpow(z, q, p)
	t = fpow(n, q, p)
	r = fpow(n, (q + 1) // 2, p)
	m = s
	while t % p != 1:
		i = 1
		while fpow(t, 2 ** i, p) != 1:
			i += 1
		b = fpow(c, 2 ** (m - i - 1), p)
		r = r * b % p
		c = b * b % p
		t = t * c % p
		m = i
	if r < p - r:
		return r
	return p - r

n = 7705321458598879497
q = 12979492918818656033
r = msqrt(n, q)

assert(r * r % q == n)

print("cnss{%d}" % r)
