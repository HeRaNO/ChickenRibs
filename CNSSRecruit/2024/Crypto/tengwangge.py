from hashlib import sha256

def exgcd(a, b):
	if b == 0:
		return a, 1, 0
	res, x, y = exgcd(b, a % b)
	return res, y, x - (a // b) * y

def liEu(a, b, n):
	d, x, y = exgcd(a, n)
	if b % d != 0:
		return False
	n = n // d
	return ((x * b // d) % n + n) % n

N = 2**32
x = [1191871952, 424959397, 2071728008]
a = liEu((x[0] - x[1] + N) % N, (x[1] - x[2] + N) % N, N)
b = (x[1] - x[0] * a % N + N) % N
print(a, b)

for i in range(7):
	x.append((x[-1] * a + b) % N)
print(len(x))
print("cnss{" + sha256(str(x).encode()).digest().hex() + "}")
