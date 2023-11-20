from sage.all import *
from Crypto.Util.number import *

n = 3322653117860796307881702118715938603299933196422318170688239817538863269879196751517883984368101175912757699818959313188577820238991745748791220070657861
h = 2124833808496595853801133466156124859021541288125712571058299295082272671181015365259674266573518307514981326822864098542354452199064749348011358863682094
g = 7

primes, exponents = zip(*factor(n))
primes = primes[:-1]
dlogs = []
pri = []

for fac in primes:
    R = GF(fac)
    dlog = R(h).log(R(g))
    dlogs.append(dlog)
    pri.append(fac - 1)

l = crt(list(dlogs), list(pri))
print(long_to_bytes(l).decode())
