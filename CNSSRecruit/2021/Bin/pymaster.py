'''
l = len(s)
a = []

for i in range(l):
	a.append((ord(s[i]) ^ ord('a')) + 14)
'''

a = [16, 29, 32, 32, 40, 67, 23, 22, 32, 76, 22, 32, 76, 35, 23, 18, 76, 19, 22, 32, 76, 28, 21, 76, 35, 23, 18, 76, 31, 38, 35, 23, 28, 29, 42]
s = ""

for i in a:
	s += chr((i - 14) ^ 97)

print(s)
