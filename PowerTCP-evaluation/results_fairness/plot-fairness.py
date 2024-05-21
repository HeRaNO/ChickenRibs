import sys
import matplotlib.pyplot as plt

algs = [('dcqcn', 'DCQCN'), ('dctcp', 'DCTCP'),
		('hpcc', 'HPCC'), ('timely', 'TIMELY'),
		('powerInt', 'PowerTCP - INT'), ('powerDelay', 'PowerTCP - Delay')]

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

for now_analyze, title in algs:
	time_1, tput_1 = read(now_analyze, 1)
	time_2, tput_2 = read(now_analyze, 2)
	time_3, tput_3 = read(now_analyze, 3)
	time_4, tput_4 = read(now_analyze, 4)

	assert time_1 == time_2
	assert time_2 == time_3
	assert time_3 == time_4

	plt.plot(time_1, tput_1, label='flow-1', color = 'red')
	plt.plot(time_1, tput_2, label='flow-2', color = 'brown')
	plt.plot(time_1, tput_3, label='flow-3', color = 'green')
	plt.plot(time_1, tput_4, label='flow-4', color = 'blue')
	plt.title(title)

	plt.tight_layout(pad=1.0)
	plt.savefig(f'{now_analyze}.png')
