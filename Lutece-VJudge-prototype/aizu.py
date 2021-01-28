import requests
import json
import sys

username = "" # Fill it
passwd = "" # Fill it

session = requests.Session()

url = 'https://judgeapi.u-aizu.ac.jp'

loginUrl = url + '/session'

formData = {
	'id': username,
	'password': passwd,
}

headers = {'content-type': "application/json"}

r = session.post(loginUrl, data = json.dumps(formData), headers = headers, verify = False)

codeFile = open("1.cpp", "r")
code = codeFile.read()

subUrl = url + '/submissions'

formData = {
	"problemId": "0000",
	"language": "C++17",
	"sourceCode": code
}

r = session.post(subUrl, data = json.dumps(formData), headers = headers, verify = False)

print(r.text)

verUrl = url + '/submission_records/users/HeRaNO?page=0'

r = session.get(verUrl, verify = False)

print(r.text)
