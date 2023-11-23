import random
import string
import argparse

char_table = string.digits + string.ascii_lowercase
random.seed()

parser = argparse.ArgumentParser(description='Generate passwords for DOMjudge users.')
parser.add_argument('-n', type=int, default=10, help='Number of users')
parser.add_argument('-L', type=int, default=8, help='Length of passwords')
args = parser.parse_args()

B = len(char_table)

def f(x):
	v = ''
	while x:
		x, i = divmod(x, len(char_table))
		v = char_table[i] + v
	return v.rjust(args.L, '0')

for i in range(args.n):
	print(f(random.randint(0, B ** args.L)))
