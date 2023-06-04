warmup = []
contest = []

pos = []

with open('pwdlet_warmup.tsv', encoding='utf-8') as f:
	for line in f:
		x = line.strip().split('\t')
		warmup.append(['team', x[1], 'warmup_' + x[2], x[3]])
		pos.append((int(x[2][-3:]), x[0]))

with open('pwdlet.tsv', encoding='utf-8') as f:
	for line in f:
		x = line.strip().split('\t')
		contest.append(['team'] + x[1:])

with open('pwdlet_warmup_converted.tsv', 'w', encoding='utf-8') as f:
	f.write('accounts\t1\n')
	for x in warmup:
		f.write('\t'.join(x))
		f.write('\n')

with open('pwdlet_converted.tsv', 'w', encoding='utf-8') as f:
	f.write('accounts\t1\n')
	for x in contest:
		f.write('\t'.join(x))
		f.write('\n')

with open('add_room.sql', 'w', encoding='utf-8') as f:
	sorted(pos, key=lambda x:x[0])
	for i, p in pos:
		f.write(f'update team set room = \'{p}\' where teamid = {i};\n')
