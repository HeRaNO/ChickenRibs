from pwn import *

host = "119.3.83.106"
port = 10011

s = remote(host, port)

x = s.recvline().decode().strip()
print(x)
result = re.split(r'[*|=?]', x)
result = str(int(result[0]) * int(result[1]))
s.sendline(result.encode())

s.interactive()
s.close()
