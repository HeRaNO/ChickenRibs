from pwn import *

io = remote('43.156.14.141', 1141)

print(io.recvuntil(b'(y/n)\n').decode().strip())
io.sendline(b'y')
print(io.recvline().decode().strip())
io.sendline(b'y')

for i in range(100):
	x = io.recvline().decode().strip().split()
	task = x[0] + x[1] + x[2]
	print(task)
	result = eval(task)
	io.sendline(f'{result}\n'.encode())

io.sendline(b'cat flag')
print(io.recvline().decode().strip())

# print(io.recvline().decode().strip())
# io.interactive()
