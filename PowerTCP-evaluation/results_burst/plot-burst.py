import sys
import matplotlib.pyplot as plt

algs = [('dcqcn', 'DCQCN'), ('dctcp', 'DCTCP'),
		('hpcc', 'HPCC'), ('timely', 'TIMELY'),
		('powerInt', 'PowerTCP - INT'), ('powerDelay', 'PowerTCP - Delay')]

for alg, title in algs:
	time = []
	qlen = []
	tput = []
	with open(f'result-{alg}.burst', 'r') as f:
		for line in f:
			t = line.strip().split()
			nowTime = float(t[11])
			nowQlen = int(t[9])
			nowTput = (int(t[7]) * 8) / (nowTime - time[-1]) if len(time) != 0 else 0
			nowQlen /= 2 ** 10 # Convert to KiB
			nowTput /= 2 ** 30 # Convert to GiB
			time.append(nowTime)
			qlen.append(nowQlen)
			tput.append(nowTput)

		fig, ax = plt.subplots()

		line1, = ax.plot(time, tput, label='Throughput', color='blue')
		ax.set_xlabel('Time (ms)')
		ax.set_ylabel('Throughput (Gbps)')

		ax2 = ax.twinx()
		line2, = ax2.plot(time, qlen, label='Qlen', color='red')
		ax2.set_ylabel('Queue length (KB)')

		ax.set_title(title)
		ax.legend(handles=[line1, line2], loc='upper left')

		plt.tight_layout(pad=1.0)
		plt.savefig(f'{alg}.png')
