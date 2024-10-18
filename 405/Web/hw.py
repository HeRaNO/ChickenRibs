import requests

session = requests.Session()

cookies = {
	"icecream": "good",
	"friedchicken": "nice"
}

header = {
	"To" : "Doraemon"
}

url = "http://405.trainoi.com:27266/?spell=viwo50"

data = b"\xaa\xbb\xcc\xdd"

r = session.post(url, cookies=cookies, headers=header, data=data)
print(r.text)
