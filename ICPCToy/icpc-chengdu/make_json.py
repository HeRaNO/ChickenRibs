import json
import random
import string
import argparse

random.seed()

pinyin = []

with open('pinyin-table.txt', 'r') as f:
	for line in f:
		pinyin.append(line.strip())

L = 10

with open("seats.json") as f:
	pos_ip_map = json.loads(f.read())

print(pos_ip_map["F18"])

def gen_passwd(length):
	pwd_part = []
	len_sum = 0
	while len_sum < length:
		t = random.choice(pinyin)
		pwd_part.append(t)
		len_sum += len(t)
	return '-'.join(pwd_part)

all_team = open('seats-all.csv', encoding='utf-8')

affiliations_id_dict = {}
affiliations_id = 1

teams = []
team_id = 1

accounts = []
accounts_warmup = []
passwd_let = {}
passwd_let_warmup = {}
org_map = {}

def get_group_id(info):
	res = group_id_dict.get(info)
	if res is None:
		raise RuntimeError(f'no group with name {info}')
	return res

def make_members(members):
	res = ''
	for member in members:
		if member != '':
			res += f', {member}'
	return res[2:]

def get_affiliation_id(org):
	global affiliations_id
	res = affiliations_id_dict.get(org)
	if res is None:
		affiliations_id_dict[org] = affiliations_id
		res = affiliations_id
		affiliations_id += 1
	return res

for team in all_team:
	team_info = team.strip().split(',')
	print(team_info)
	team_pos = team_info[5]
	print(team_pos)
	team_pos = team_pos[0] + team_pos[1:].rjust(2, '0')
	print(team_pos)
	teams.append({
		'id': team_pos,
		'group_ids': ["participants"],
		'name': team_info[1],
		'members': make_members(team_info[2:5]),
		'organization_id': f'org_{get_affiliation_id(team_info[0])}',
		'room': team_pos
	})
	pwd = gen_passwd(L)
	pwd_warmup = gen_passwd(L)
	accounts.append({
		'id': f'account_{team_id}',
		'username': 'team%03d' % (team_id),
		'password': pwd,
		'type': 'team',
		'team_id': team_pos,
		'ip': pos_ip_map[team_pos]
	})
	accounts_warmup.append({
		'id': f'warmup_account_{team_id}',
		'username': 'warmup_team%03d' % (team_id),
		'password': pwd_warmup,
		'type': 'team',
		'team_id': team_pos,
		'ip': pos_ip_map[team_pos]
	})
	passwd_let[team_pos] = [team_info[1], 'team%03d' % (team_id), pwd]
	passwd_let_warmup[team_pos] = [team_info[1], 'warmup_team%03d' % (team_id), pwd_warmup]
	team_id += 1

affiliations = []

for name in affiliations_id_dict:
	org_id = f'org_{str(affiliations_id_dict[name])}'
	affiliations.append({
		'id': org_id,
		'name': name,
		'formal_name': name,
		'country': 'CHN'
	})
	org_map[org_id] = name

with open('organizations.json', 'w', encoding='utf-8') as f:
	f.write(json.dumps(affiliations, ensure_ascii=False))

with open('org-map.txt', 'w', encoding='utf-8') as f:
	for org_id in org_map.keys():
		f.write(' '.join([org_id, org_map[org_id]]))
		f.write("\n")

with open('teams.json', 'w', encoding='utf-8') as f:
	f.write(json.dumps(teams, ensure_ascii=False))

with open('accounts.json', 'w', encoding='utf-8') as f:
	f.write(json.dumps(accounts, ensure_ascii=False))

with open('accounts_warmup.json', 'w', encoding='utf-8') as f:
	f.write(json.dumps(accounts_warmup, ensure_ascii=False))

with open('pwdlet.tsv', 'w', encoding='utf-8') as f:
	for k in sorted(passwd_let.keys(), key=lambda x: (ord(x[0]) - ord('A') + 1) * 100 + int(x[1:])):
		f.write('\t'.join([k] + passwd_let[k]))
		f.write('\n')

with open('pwdlet_warmup.tsv', 'w', encoding='utf-8') as f:
	for k in sorted(passwd_let_warmup.keys(), key=lambda x: (ord(x[0]) - ord('A') + 1) * 100 + int(x[1:])):
		f.write('\t'.join([k] + passwd_let_warmup[k]))
		f.write('\n')
