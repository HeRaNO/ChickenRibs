import random

random.seed()
n = int(input("Input the number of teams: "))

def f(x):
	v = []
	while x > 0:
		t = x % 36
		if t >= 10:
			v.append(chr(t + 87))
		else:
			v.append(chr(t + 48))
		x = x // 36
	while len(v) < 6:
		v.append('0')
	v.reverse()
	return "".join(str(i) for i in v)

for i in range(0, n):
	print(f(random.randint(1, 36 ** 6)))
