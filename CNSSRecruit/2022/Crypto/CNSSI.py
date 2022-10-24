from Crypto.Util.number import long_to_bytes

m = [16301931288229500743, 10688720137201015289, 16911712564752263939, 18437066330147745443, 17860816637853481777]
a = [7934156186679581854, 5731037063100123714, 8436108005474466628, 10744368611052783817, 16691490606000191965]

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

print(long_to_bytes(exCRT(5)).decode())
