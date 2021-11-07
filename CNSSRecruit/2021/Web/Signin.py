import requests

session = requests.Session()
payload = {
	"CNSS": "join"
}
cookies = {
	"flag": "1"
}
r = session.post("http://121.41.7.149:60001/?web=like", payload, cookies = cookies)
print(r.text)
