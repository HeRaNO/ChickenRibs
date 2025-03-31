import os

stat = """# Description #


# Input #


# Output #


# Samples #

```input1

```

```output1

```

# Note #


# Resources #
The 23rd UESTC Programming Contest Preliminary"""

prob = """title: {{Name}}
tag:
- Lutece
- 校赛
- 初赛
- 2025
pid: {{ProbID}}"""

conf = """type: default
time: {{TL}}ms
memory: {{ML}}m
subtasks:
- score: 100
  if: []
  id: 1
  type: min
  cases:
"""

pid = 3387

for i in "ABCDEFGHIJKLMNOPQ":
	with open(f"{i}\\problem_zh.md", "w") as f:
		f.write(stat)
	testcases = []
	for file_name in os.listdir(f"{i}\\testdata"):
		tid, ext = file_name.split(".")
		if tid not in testcases:
			testcases.append(tid)
	testcases.sort()
	my_conf = conf
	for name in testcases:
		my_conf += f"  - input: {name}.in\n    output: {name}.ans\n"
	with open(f"{i}\\domjudge-problem.ini") as f:
		for line in f:
			x = line.split()
			if x[0] == "timelimit":
				tl = int(float(x[2]) * 1000)
	with open(f"{i}\\_problem.yaml", encoding="utf-8") as f:
		for line in f:
			x = line.split(":")
			if x[0].strip() == "memory":
				ml = x[1].strip()
			if x[0].strip() == "name":
				name = x[1].strip()
	with open(f"{i}\\testdata\\config.yaml", "w", encoding="utf-8") as f:
		f.write(my_conf.replace("{{TL}}", str(tl)).replace("{{ML}}", ml))
	with open(f"{i}\\problem.yaml", "w", encoding="utf-8") as f:
		my_prob = prob
		f.write(my_prob.replace("{{Name}}", name).replace("{{ProbID}}", f"Lutece{pid}"))
	pid += 1
