import os
import json
import base64
import getpass
import requests
from requests.auth import HTTPBasicAuth

usr = None
passwd = None

hostURL = input("Input the Host URL: ")
hostURL.strip()

cid = input("Input the Contest ID: ")
cid.strip()

usr = None
passwd = None

submissionURL = hostURL + "/api/v4/contests/" + cid + "/submissions/"

def getSubmissions():
	s = None

	print("Need login to the administrator account.")
	while True:
		usr = input("Input the username: ").strip()
		passwd = getpass.getpass("Input the password: ").strip()
		s = requests.get(submissionURL, auth = HTTPBasicAuth(usr, passwd))
		if s.status_code == 200:
			break
		elif s.status_code == 401:
			print("Login failed.")
		else:
			raise RuntimeError('Website returns status code: %d. Check your Contest ID!' % (s.status_code))

	assert s.status_code == 200
	return json.loads(s.text), usr, passwd

def downloadSubmission(rec, usr, passwd):
	subId = rec["id"]

	fileURL = submissionURL + subId + "/source-code"
	s = None
	if usr != None and passwd != None:
		s = requests.get(fileURL, auth = HTTPBasicAuth(usr, passwd))
		if s.status_code == 404:
			print("Submission " + subId + " not found!")
			return 0
	else:
		print("Need login to the administrator account.")
		while True:
			usr = input("Input the username: ").strip()
			passwd = getpass.getpass("Input the password: ").strip()
			s = requests.get(fileURL, auth = HTTPBasicAuth(usr, passwd))
			if s.status_code == 200:
				break
			elif s.status_code == 404:
				print("Submission " + subId + " not found!")
				return 0

	codePath = "submissions/" + rec["problem_id"] + "/"
	if os.path.exists(codePath) == False:
		os.mkdir(codePath)

	file = json.loads(s.text)[0]
	fileName = rec["team_id"] + "-" + subId + "-" + file["filename"]
	filePath = codePath + fileName
	code = file["source"]
	try:
		code = base64.b64decode(code).decode("utf-8")
		f = open(filePath, "w", encoding = "utf-8")
		f.write(code)
		f.close()
	except Exception as e:
		try:
			print("Try decoding with GBK...")
			code = base64.b64decode(code).decode("gbk")
			f = open(filePath, "w", encoding = "gbk")
			f.write(code)
			f.close()
		except Exception as ee:
			print("Submission " + subId +" downloaded unsuccessfully.")
			print(ee)
			return 0

	print("Submission " + subId +" downloaded successfully.")
	return 1

subList, usr, passwd = getSubmissions()
allSubmissionsCnt = len(subList)
print(str(allSubmissionsCnt) + " submission(s) found.")

if os.path.exists("submissions/") == False:
	os.mkdir("submissions/")

suc = 0

for rec in subList:
	suc += downloadSubmission(rec, usr, passwd)

print("%d of %d submission(s) downloaded successfully." % (suc, allSubmissionsCnt))
