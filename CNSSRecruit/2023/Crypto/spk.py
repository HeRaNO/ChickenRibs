from Crypto.Util.number import long_to_bytes
from gmpy2 import gcd, iroot

# Rational numbers have finite a continued fraction expansion.
def get_cf_expansion(n, d):
    e = []
    q = n // d
    r = n % d
    
    e.append(q)

    while r != 0:
        n, d = d, r           
        q = n // d
        r = n % d
        e.append(q)

    return e

def get_convergents(e):
    n = [] # Nominators
    d = [] # Denominators

    for i in range(len(e)):
        if i == 0:
            ni = e[i]
            di = 1
        elif i == 1:
            ni = e[i]*e[i-1] + 1
            di = e[i]
        else: # i > 1 
            ni = e[i]*n[i-1] + n[i-2]
            di = e[i]*d[i-1] + d[i-2]

        n.append(ni)
        d.append(di)
        yield (ni, di)

e = 99229505005010231229812309405118621210000665411317929329600320339351298536042106221904006618372016899838834315350282056201576780947332634472383794182914396787560149770087768346108970874622698958641239168672884943722683097496196568051260666405536471900271607250500649553508481028777575476228205350216263899864839231023168979708315202587104442940310612179957452668838181940302165426024768292895768359058100485442771122055233699699591861456009579197208612724634653
N = 777932066471261253953635643543769273870576807001853821365002899038017652136640326606707541086305255419688451331308105858262381681205657118149670724969402173491693110671887550886032285747295962582655746980079520315019448934437742771629769039207570002600238133829941166519652324878087610266956030449933384381670213413005273221487049001640280300893616812980727738757188984406451974046745624206457936867759992076616467784551949417643382015447862723484003189099322113
C = 315162533057119030644069576898014821746187831990641977888442441986396488578480924344830827691640071104116111429579458497274291449212879753454215527936892759921631840278976085540574066181311866181244489267112630519512826615435097016920565522260797348024774745088674028891909401404506165402416608686728774514537539009768594970540227164117320018763121106885108998344223691343126585144804733329828035450075042672319188914135360404008915353519214959250876459809490891

crt, _ = iroot(N, 3)

cf_expansion = get_cf_expansion(e, N - (2 * crt ** 2 - crt))
convergents = get_convergents(cf_expansion)

p, q = 0, 0

for pk, pd in convergents: # pk - possible k, pd - possible d
    if pk == 0:
        continue

    possible_phi = (e*pd - 1)//pk
    g = gcd(possible_phi, N)
    if 1 < g and g < N:
        p = g
        q = N // (g ** 2)
        if p ** 2 * q != N:
            q = g
            p, _ = iroot(N / q, 2)
        break

phi = p * (p - 1) * (q - 1)
d = pow(e, -1, phi)
print(long_to_bytes(pow(C, d, N)).decode())
