import requests

session = requests.Session()

username = "" # Fill it
passwd = "" # Fill it

url = "http://poj.org/login"

formData = {
	"user_id1": username,
	"password1": passwd,
	"B1": "login",
	"url": "."
}

r = session.post(url, formData)

# page = open("out.html", "w", encoding = "utf-8")
# page.write(r.text)

url = "http://poj.org/submit"

codeFile = open("1000.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	"problem_id": "1000",
	"language": "0", # 0 for G++
	"source": code,
	"submit": "Submit",
	"encoded": "0"
}

r = session.post(url, formData)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
