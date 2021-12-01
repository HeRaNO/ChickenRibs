contestants = 589 # Number of constants
problems = ['airport', 'bracket', 'palin', 'traffic'] # Problem name
suffixes = ['.c', '.cpp', '.pas']
IDLen = 5 # Length of each ID

for contestant in range(1, contestants + 1):
	folder = "SC-" + str(contestant).zfill(IDLen)
	for problem in problems:
		for suffix in suffixes:
			path = folder + '\\' + problem + '\\' + problem + suffix
			try:
				with open(path, 'r') as f:
					code = f.read().lower()
					if 'ccf' in code:
						print(folder + "/" + problem)
			except IOError:
				pass
			except UnicodeDecodeError:
				with open(path, 'r', encoding="utf-8") as f:
					code = f.read().lower()
					if 'ccf' in code:
						print(folder + "/" + problem)
			except Exception as e:
				print(e)
