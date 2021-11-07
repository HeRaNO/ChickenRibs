dic = '0987654321qwertyuioplkjhgfdsazxcvbnmQWERTYUIOPLKJHGFDSAZXCVBNM!@#$%^&*-=+:;(){}<>'
cy = 'eJ:zwWufwZuYwHsvelcawj9le^jxwCMb7HjhwZuYwJMz7JVl7Hugq^3j7Zob1)qQeZuke7Hj7J:n4RZze^jU1x-ge%Ige%IuqHjmeCHzwRMte^nge(ZhqHqkqKWue%MO0987'
msg = ''
n = len(cy)

revMap = {}
for i in range(len(dic)):
    revMap[dic[i]] = i

def dec_to_ter(num):
    l = []
    while True:
        num, reminder = divmod(num, 3)
        l.append(str(reminder))
        if num == 0:
            return "".join(l[::-1]).zfill(4)

for i in range(n >> 2):
    ori = dec_to_ter(revMap[cy[i << 2]]) + dec_to_ter(
           revMap[cy[i << 2 | 1]]) + dec_to_ter(
           revMap[cy[i << 2 | 2]]) + dec_to_ter(
           revMap[cy[i << 2 | 3]])
    print(ori)
    assert len(ori) == 16
    ori = ori[1:]
    msg += chr(int(ori[:5], 3)) + chr(int(ori[5: 10], 3)) + chr(int(ori[10:], 3))

print(msg)
