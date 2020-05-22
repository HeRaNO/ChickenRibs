import sys
import urllib3
from bs4 import BeautifulSoup

urllib3.disable_warnings()
http = urllib3.PoolManager()

headers = {
	'User-Agent':'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/60.0.3112.113 Safari/537.36'
}

def get(url):
	r = http.request('GET', url)
	return BeautifulSoup(r.data, features="lxml")

cnt = [0 for i in range(101)]
compile_error = 0

pt = 1
while pt <= 348500:
	print(pt, file = sys.stderr)
	page = get('http://uoj.ac/submission/'+str(pt))
	t = page.title.contents[0]
	if t[0] == '4':
		pt += 1
		continue
	s = page.select('a.uoj-score')
	if len(s):
		score = int(s[0].contents[0])
		cnt[score] += 1
	else:
		compile_error += 1
	pt += 1

for i in range(0,101):
	print(i,' ', cnt[i])

print("Compile Error: ", compile_error)
