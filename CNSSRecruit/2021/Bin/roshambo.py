from pwn import *

host = "120.25.225.38"
port = 2556

s = remote(host, port)

print(s.recvline().decode().strip())
print(s.recvline().decode().strip())
print(s.recvuntil(b".").decode().strip())
s.sendline(b"\n")

for i in range(50):
    s.recvline()
    print(s.recvline().decode().strip())
    x = s.recvline().decode().strip()
    print(x)
    print(s.recvuntil(b":").decode().strip(), end = " ")
    if x == "scissors":
        s.sendline(b"rock\n")
        print("rock")
    if x == "rock":
        s.sendline(b"cloth\n")
        print("cloth")
    if x == "cloth":
        s.sendline(b"scissors\n")
        print("scissors")

s.interactive()
s.close()
