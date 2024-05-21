algs = ['dcqcn', 'dctcp', 'hpcc', 'powerDelay', 'powerInt', 'timely']
loads = ['0.2', '0.4', '0.6', '0.8', '0.9', '0.95']
req = '0'
query = '0'

for alg in algs:
	for load in loads:
		fct_slowdown = []
		with open(f'result-{alg}-{load}-{req}-{query}.fct', 'r') as f:
			for line in f:
				x = line.strip().split()
				fct, base_fct = int(x[1]), int(x[5])
				fct_slowdown.append(fct / base_fct)
		fct_slowdown.sort()
		if len(fct_slowdown) != 0:
			print(f'Alg: {alg} Load: {load} P99 FCT Slowdown: {fct_slowdown[int(len(fct_slowdown) - 1) * 99 // 100]}')
			print(f'Alg: {alg} Load: {load} P999 FCT Slowdown: {fct_slowdown[int(len(fct_slowdown) - 1) * 999 // 1000]}')
