# pinyin-table.txt is from https://blog.csdn.net/Likianta/article/details/87871183
import random
import argparse

random.seed()

parser = argparse.ArgumentParser(description='Generate passwords for DOMjudge users.')
parser.add_argument('-n', type=int, default=10, help='Number of users')
parser.add_argument('-L', type=int, default=8, help='Length of passwords')
args = parser.parse_args()

pinyin = []

with open('pinyin-table.txt', 'r') as f:
	for line in f:
		pinyin.append(line.strip())

for i in range(args.n):
	pwd_part = []
	len_sum = 0
	while len_sum < args.L:
		t = random.choice(pinyin)
		pwd_part.append(t)
		len_sum += len(t)
	print('-'.join(pwd_part))
