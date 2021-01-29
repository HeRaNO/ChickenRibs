import requests

session = requests.Session()

JUDGE_ID = "" # Fill it

url = "https://acm.timus.ru/submit.aspx"

codeFile = open("1000.cpp", "r", encoding = "utf-8")
code = codeFile.read()

formData = {
	"Action": "submit",
	"SpaceID": "1",
	"JudgeID": JUDGE_ID,
	"Language": "68", # 68 for G++ 9.2 x64
	"ProblemNum": "1000",
	"Source": code
}

files = {"SourceFile": None}

r = session.post(url, data = formData, files = files, verify = False)

page = open("out.html", "w", encoding = "utf-8")
page.write(r.text)
