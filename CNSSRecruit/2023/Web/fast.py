import re
import requests
from hashlib import md5

session = requests.Session()

r = session.get('http://124.221.34.13:55590')

regKey = r'Key : (.+)<span id=\"variable\"></span>'

key = re.findall(regKey, r.text)[0]

r = session.get(f'http://124.221.34.13:55590/check?value={md5(key.encode()).hexdigest()}')

print(r.text)
