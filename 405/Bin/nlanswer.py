from pwn import *

io = remote('405.trainoi.com', 27070)

io.sendline(b'A')
io.sendline(b'A')
io.sendline(b'B')
io.sendline(b'D')
io.sendline(b'C')
io.sendline(b'D')
io.sendline(b'C')
io.sendline(b'C')
io.sendline(b'D')
io.sendline(b'A')
io.sendline(b'C')
io.sendline(b'A')
io.sendline(b'B')
io.sendline(b'C')
io.sendline(b'C')
io.sendline(b'B')
io.sendline(b'D')
io.sendline(b'A')
io.interactive()
