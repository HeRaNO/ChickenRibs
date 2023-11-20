import re
from pwn import *

# context.log_level = 'debug'

io = remote('43.156.14.141', 1141)

regUser = r'\[USER\].*: (.+)'
regSys = r'\[SYSTEM\]\[(.+)\]\(([0-9]+)pt\)--(.+)\(([0-9]+)pt\)'

for i in range(100):
	x = io.recvuntil(b'> ').decode().strip()
	print(x)
	if x[:6] == '[USER]':
		cmd = re.match(regUser, x).group(1)
		if cmd == '#ping':
			io.sendline(b'pong!')
		else:
			io.sendline(f'The command {cmd} does not exist.'.encode())
	else:
		cmd = re.match(regSys, x)
		name = cmd.group(1)
		oriPoint = int(cmd.group(2))
		taskName = cmd.group(3)
		addPoint = int(cmd.group(4))
		io.sendline(f'Congratulations to {name} for passing {taskName}, current score is {oriPoint + addPoint} points!'.encode())

io.sendline(b'cat /flag')
print(io.recvline().decode().strip())
io.close()
