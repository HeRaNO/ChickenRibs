import sys
import matplotlib.pyplot as plt

time = []
qlen = []
tput = []

with open(sys.argv[1], 'r') as f:
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

def plot(time, throughput, qlen, save_path):
	fig, ax = plt.subplots()

	line1, = ax.plot(time, throughput, label='Throughput', color='blue')
	ax.set_xlabel('Time (ms)')
	ax.set_ylabel('Throughput (Gbps)')

	ax2 = ax.twinx()
	line2, = ax2.plot(time, qlen, label='Qlen', color='red')
	ax2.set_ylabel('Queue length (KB)')

	ax.set_title("TIMELY")
	ax.legend(handles=[line1, line2], loc='upper left')

	plt.tight_layout(pad=1.0)
	plt.savefig(save_path)

plot(time, tput, qlen, "timely.png")
