import json
import random

all_team = open('do_tsv.tsv', encoding='utf-8')

random.seed()

pinyin = []

with open('pinyin-table.txt', 'r') as f:
	for line in f:
		pinyin.append(line.strip())

group_id_dict = {
	'普通名额': 'participants',
	'普通队伍': 'participants',
	'打星队伍': 'observers',
	'女生队伍': 'organization'
}

affiliations_id_dict = {}
affiliations_id = 1

teams = []
team_id = 1

accounts = []
passwd_let = {}
accounts_warmup = []
passwd_let_warmup = {}

def gen_passwd(length):
	pwd_part = []
	len_sum = 0
	while len_sum < length:
		t = random.choice(pinyin)
		pwd_part.append(t)
		len_sum += len(t)
	return '-'.join(pwd_part)

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
	team_info = team.strip().split('\t')
	print(team_info)
	teams.append({
		'id': f'team_{team_id}',
		'group_ids': [get_group_id(team_info[3])],
		'name': team_info[2],
		'members': make_members(team_info[4:7]),
		'organization_id': f'org_{get_affiliation_id(team_info[1])}',
		'room': team_info[7]
	})
	pwd = gen_passwd(10)
	pwd_warmup = gen_passwd(10)
	accounts.append({
		'id': f'account_{team_id}',
		'username': 'team%03d' % (team_id),
		'password': pwd,
		'type': 'team',
		'team_id': f'team_{team_id}',
	})
	passwd_let[team_info[7]] = [team_info[2], 'team%03d' % (team_id), pwd]
	accounts_warmup.append({
		'id': f'warmup_account_{team_id}',
		'username': 'warmup_team%03d' % (team_id),
		'password': pwd_warmup,
		'type': 'team',
		'team_id': f'team_{team_id}',
	})
	passwd_let_warmup[team_info[7]] = [team_info[2], 'warmup_team%03d' % (team_id), pwd_warmup]
	team_id += 1

affiliations = []

for name in affiliations_id_dict:
	affiliations.append({
		'id': f'org_{str(affiliations_id_dict[name])}',
		'name': name,
		'formal_name': name,
		'country': 'CHN'
	})

with open('organizations.json', 'w', encoding='utf-8') as f:
	f.write(json.dumps(affiliations, ensure_ascii=False))

with open('teams.json', 'w', encoding='utf-8') as f:
	f.write(json.dumps(teams, ensure_ascii=False))

with open('accounts.json', 'w', encoding='utf-8') as f:
	f.write(json.dumps(accounts, ensure_ascii=False))

with open('accounts_warmup.json', 'w', encoding='utf-8') as f:
	f.write(json.dumps(accounts_warmup, ensure_ascii=False))

with open('pwdlet.tsv', 'w', encoding='utf-8') as f:
	for k in sorted(passwd_let.keys(), key=lambda x: (ord(x[-1]) - ord('A') + 1) * 100 + int(x[: -1])):
		f.write('\t'.join([k] + passwd_let[k]))
		f.write('\n')

with open('pwdlet_warmup.tsv', 'w', encoding='utf-8') as f:
	for k in sorted(passwd_let_warmup.keys(), key=lambda x: (ord(x[-1]) - ord('A') + 1) * 100 + int(x[: -1])):
		f.write('\t'.join([k] + passwd_let_warmup[k]))
		f.write('\n')
