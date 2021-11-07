from sage.all import *

p = 941958815880242161
G = GF(p)

def f(a, b):
    if a == 0 or b == 0:
        return 0
    a = G(a)
    b = G(b)
    prod = G(a)
    ret = 1
    while True:
        try:
            discrete_log(prod, b)
        except Exception as e:
            pass
        else:
            return ret
        finally:
            prod = prod * a
            ret += 1

flag = 0
mask = (1 << 128) - 1
k1, k2 = (12345678987654321, 98765432123456789)

for i in range(1000):
    s = ""
    for i in range(10):
        k1, k2 = ((k1 * k1 + k2) & mask, (k2 * k2 + k1) & mask)
        s += str(f(k1 % p, k2 % p))
    
    flag ^= int(s)

print("Flag is cnss{%d}" % flag)
