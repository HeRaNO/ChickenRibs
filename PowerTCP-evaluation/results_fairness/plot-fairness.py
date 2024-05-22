import matplotlib.pyplot as plt

algs = [('dcqcn', 'DCQCN'), ('dctcp', 'DCTCP'),
		('hpcc', 'HPCC'), ('timely', 'TIMELY'),
		('powerInt', 'PowerTCP - INT'), ('powerDelay', 'PowerTCP - Delay')]

for now_analyze, title in algs:
	def read(s, i):
		time = []
		tput = []
		filename = f'result-{s}.{i}'
		with open(filename, 'r') as f:
			for line in f:
				t = line.strip().split()
				nowTime = float(t[7])
				nowTput = float(t[5])
				nowTput /= 2 ** 30 # Convert to GiB
				time.append(nowTime)
				tput.append(nowTput)
		return time, tput

	time_1, tput_1 = read(now_analyze, 1)
	time_2, tput_2 = read(now_analyze, 2)
	time_3, tput_3 = read(now_analyze, 3)
	time_4, tput_4 = read(now_analyze, 4)

	assert time_1 == time_2
	assert time_2 == time_3
	assert time_3 == time_4
	fig, ax = plt.subplots()

	line1, = ax.plot(time_1, tput_1, label='Flow-1', color='red')
	line2, = ax.plot(time_1, tput_2, label='Flow-2', color='brown')
	line3, = ax.plot(time_1, tput_3, label='Flow-3', color='green')
	line4, = ax.plot(time_1, tput_4, label='Flow-4', color='blue')
	ax.set_xlabel('Time (ms)')
	ax.set_ylabel('Throughput (Gbps)')

	ax.set_title(title)
	ax.legend(handles=[line1, line2, line3, line4], loc='upper right')

	plt.title(title)

	plt.tight_layout(pad=1.0)
	plt.savefig(f'{now_analyze}.png')
