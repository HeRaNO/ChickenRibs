#!/usr/bin/env python
# -*- coding: UTF-8 -*-

# Using this, you can create standard problem files for HUSTOJ.
# 通过本程序，可以为 HUSTOJ 的题目创建标准题目文件夹。

# You can find the defination of the 'standard problem files' at Readme.
# 可以在 Readme 中找到标准题目格式文件夹的定义。

# By HeRaNO

import os
import sys
import shutil
import getpass
import MySQLdb

def DealWithPicandOther (s):
	n = len(s)
	i = 0
	while i<n:
		if s[i] == '"':
			scp = "/home/judge/src/web";
			if (s[i+1]=='/') and (s[i+2] == 'u') and (s[i+3] == 'p') and (s[i+4] == 'l') and (s[i+5] == 'o') and (s[i+6] == 'a') and (s[i+7] == 'd'):
				j = i + 1
				while s[j] != '"' and j<n:
					scp += s[j]
					j = j + 1
				i = j
				if not os.path.exists(tmp_nowpath + '/pic_and_other'):
					os.mkdir(tmp_nowpath + '/pic_and_other')
				tmp = tmp_nowpath + '/pic_and_other/' + os.path.basename(scp)
				shutil.copyfile(scp,tmp)
		i = i + 1

reload(sys)
sys.setdefaultencoding('utf8')

sqlpwd = getpass.getpass('Please input the password of root to the database!:\n 请输入数据库 root 帐号的密码！：')

if len(sqlpwd) == 0:
	sqlpwd = "root"

try:
	jol = MySQLdb.connect("localhost", "root", sqlpwd, "jol", charset='utf8')
except Exception:
	print 'Wrong password! Try again!\n 错误的密码，请重试！'
	sys.exit()

pt = jol.cursor()
pt.execute('SELECT COUNT(*) FROM problem')
ProblemCnt = pt.fetchone()[0]
print ("Now there is %d problem(s) in the HUSTOJ.\n  现在本 HUSTOJ 中共有 %d 道题目。"%(ProblemCnt,ProblemCnt))

fr = int(raw_input('Where will we start? Please tell me the problem id. If you want to start at the first one ,please input 0: \n 我们从哪里开始？请告诉我结束导出的题目编号。若要从第一题开始，请输入 0：'))
to = int(raw_input('Where will we end? Please tell me the problem id. If you want to end at the last one ,please input 0:\n 我们到哪里结束？请告诉我结束导出的题目编号。若要到最后一题结束，请输入 0：'))

if fr ==0:
	pt.execute('SELECT problem_id FROM problem LIMIT 1')
	fr = pt.fetchone()[0]

if to == 0:
	pt.execute('SELECT problem_id FROM problem ORDER BY problem_id DESC LIMIT 1')
	to = pt.fetchone()[0]

cnt = 1
datapath = "/home/judge/data/"
nowpath = os.getcwd() + '/Standard/'
if not os.path.exists(nowpath):
	os.mkdir(nowpath)

have_spj = []
have_source = []

while True:
	if fr > to:
		break
	print 'We are processing Problem %d.\n 我们正在处理 %d 题。'%(fr,fr)
	tmp_datapath = datapath + '%d'%fr

	if not os.path.exists(tmp_datapath):
		print 'This problem seems not exist.\n 这道题貌似不存在。'
		fr = fr + 1
		continue

	tmp_nowpath = nowpath + '%d'%cnt
	if os.path.exists(tmp_nowpath + '/data'):
		shutil.rmtree(tmp_nowpath + '/data')
	shutil.copytree(tmp_datapath,tmp_nowpath + '/data')
	print 'The data copy is finished!Now processing problems.\n 文件复制已结束，现在处理题面。'

	pt.execute('SELECT * FROM problem WHERE problem_id=%d'%fr)
	result = pt.fetchall()

	file = open(tmp_nowpath + '/title.txt', "w")
	file.write(result[0][1] + "\n")
	file.close()

	file = open(tmp_nowpath + '/description.txt', "w")
	file.write(str(result[0][2]) + "\n")
	file.close()
	DealWithPicandOther(result[0][2])
	

	file = open(tmp_nowpath + '/input.txt', "w")
	file.write(result[0][3] + "\n")
	file.close()
	DealWithPicandOther(result[0][3])

	file = open(tmp_nowpath + '/output.txt', "w")
	file.write(result[0][4] + "\n")
	file.close()
	DealWithPicandOther(result[0][4])

	file = open(tmp_nowpath + '/sample_input.txt', "w")
	file.write(result[0][5] + "\n")
	file.close()

	file = open(tmp_nowpath + '/sample_output.txt', "w")
	file.write(result[0][6] + "\n")
	file.close()

	file = open(tmp_nowpath + '/spj.txt', "w")
	file.write(result[0][7] + "\n")
	file.close()

	if result[0][7] == '1':
		have_spj.append(fr)

	file = open(tmp_nowpath + '/hint_and_source.txt', "w")
	file.write(result[0][8] + '\nSource: ' + result[0][9] + "\n")
	file.close()
	DealWithPicandOther(result[0][8])

	file = open(tmp_nowpath + '/limitation.txt', "w")
	file.write(str(result[0][11]) + "\n" + str(result[0][12]) + "\n")
	file.close()

	if os.path.exists(tmp_nowpath + '/pic_and_other'):
		have_source.append(fr)

	print 'Processing OK!\n 本题处理完成。'

	cnt = cnt + 1
	fr = fr + 1

print 'The last step...\n 正在进行最后一步。'

file = open(nowpath + '/problemcnt.txt', "w")
file.write('%d\n'%ProblemCnt)
file.close()

file = open(nowpath + '/have_spj.txt', "w")
n = len(have_spj)
for i in range(0,n):
	file.write('%d\n'%have_spj[i])
file.close()

file = open(nowpath + '/have_source.txt', "w")
n = len(have_source)
for i in range(0,n):
	file.write('%d\n'%have_source[i])
file.close()

print 'All finished!\n 已经完成！'
