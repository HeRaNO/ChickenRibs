# Defination of Stack.
class Stack:
	def __init__(self):
		self.sta = []
	def empty(self):
		return len(self.sta) == 0
	def push(self, x):
		self.sta.append(x)
	def top(self):
		return self.sta[len(self.sta) - 1]
	def pop(self):
		self.sta.pop()

# Part 0. Input and prepare.
s = input('Input an expression only contains numbers and \'+\', \'-\', \'*\' and \'/\':\n')
s = '0' + s
n = len(s)
cp = {'+' : 0, '-' : 0, '*' : 1, '/' : 1, '(': -1}

# Part 1. infix expression -> suffix expression.
opt = Stack()
suffix = []
i = 0
while i < n:
	if s[i] == ' ':
		i = i + 1
		continue
	if (ord(s[i]) >= 48) and (ord(s[i]) <= 57):
		p = 0
		while i < n:
			if (ord(s[i]) >= 48) and (ord(s[i]) <= 57):
				p = p * 10 + ord(s[i]) - 48
				i = i + 1
			else:
				break
		suffix.append(str(p))
		continue
	if s[i] == '(':
		opt.push(s[i])
		i = i + 1
		continue
	if s[i] == ')':
		while opt.top() != '(':
			suffix.append(opt.top())
			opt.pop()
		opt.pop()
		i = i + 1
		continue
	if opt.empty():
		opt.push(s[i])
		i = i + 1
		continue
	if opt.top == '(':
		opt.push(s[i])
		i = i + 1
		continue
	while cp[s[i]] <= cp[opt.top()]:
		suffix.append(opt.top())
		opt.pop()
		if opt.empty():
			break
	opt.push(s[i])
	i = i + 1

while not(opt.empty()):
	suffix.append(opt.top())
	opt.pop()

# Part 2. Calculate the value of the suffix expression.
n = len(suffix)
for i in range (0, n):
	if suffix[i] == '+':
		q = float(opt.top());opt.pop()
		p = float(opt.top());opt.pop()
		opt.push(p + q)
	elif suffix[i] == '-':
		q = float(opt.top());opt.pop()
		p = float(opt.top());opt.pop()
		opt.push(p - q)
	elif suffix[i] == '*':
		q = float(opt.top());opt.pop()
		p = float(opt.top());opt.pop()
		opt.push(p * q)
	elif suffix[i] == '/':
		q = float(opt.top());opt.pop()
		p = float(opt.top());opt.pop()
		opt.push(p / q)
	else:
		opt.push(suffix[i])

r = float(opt.top())
if int(r) == r:
	print ('The value of the expression is: %d'%(int(r)))
else:
	print ('The value of the expression is: %.15f'%(r))
