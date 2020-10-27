# uncompyle6 version 3.7.4
# Python bytecode 3.7 (3394)
# Decompiled from: Python 3.7.0 (v3.7.0:1bf9cc5093, Jun 27 2018, 04:06:47) [MSC v.1914 32 bit (Intel)]
# Embedded file name: py.py
# Compiled at: 2020-08-05 17:09:49
# Size of source mod 2**32: 320 bytes
import base64, operator, hashlib
inp = input('What do you want to know?\n')
encode = base64.b64encode(inp.encode('UTF-8'))
s = b'Y25zc3tmbGFnfQ=='
if operator.eq(s, encode) == True:
    hl = hashlib.md5()
    hl.update(s)
    print('The real flag is cnss{' + hl.hexdigest() + '}')
else:
    print(".pyc wouldn't tell you anything")
# okay decompiling baby_pyc.pyc
