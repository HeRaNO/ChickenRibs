if __name__ == '__main__':
	n, x = map(int, input().split())
	F = []
	for _ in range(n):
		F.append(list(map(lambda x: int(x) - 1, input().split())))
	U = [False for _ in range(x)]
	USize = x
	C = []
	while USize != 0:
		maxS = []
		maxCoverSize = 0
		for S in F:
			coverSize = 0
			for si in S:
				if U[si] == False:
					coverSize += 1
			if coverSize > maxCoverSize:
				maxCoverSize, maxS = coverSize, S
		for si in maxS:
			U[si] = True
		USize -= maxCoverSize
		C.append(maxS)
	print(len(C))
	for c in C:
		print(' '.join(map(lambda x: str(x + 1), c)))
