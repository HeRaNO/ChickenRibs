from pulp import LpMinimize, LpProblem, LpVariable, PULP_CBC_CMD, lpDot

if __name__ == '__main__':
	n, x = map(int, input().split())
	F = []
	for _ in range(n):
		F.append(list(map(lambda x: int(x) - 1, input().split())))
	def calc_max_f():
		all_f = [0 for _ in range(x)]
		for S in F:
			for si in S:
				all_f[si] += 1
		return max(all_f)
	f = calc_max_f()
	prob = LpProblem('SetCovering', LpMinimize)
	X = [LpVariable(f'x{i}', lowBound=0, upBound=1) for i in range(n)]
	prob += lpDot([1 for _ in range(n)], X)
	A = [[0 for _ in range(n)] for _ in range(x)]
	for i in range(n):
		for j in F[i]:
			A[j][i] += 1
	for i in range(x):
		prob += (lpDot(A[i], X) >= 1)
	prob.solve(PULP_CBC_CMD(msg=False))
	C = []
	for i in range(n):
		if X[i].value() * f >= 1:
			C.append(F[i])
	print(len(C))
	for c in C:
		print(' '.join(map(lambda x: str(x + 1), c)))
