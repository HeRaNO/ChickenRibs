import csv
from pathlib import Path

banner = open("easy-achivements-icpc.svg", "r", encoding="utf-8").read()

out_pos = Path(".") / "all_banner"

with open("seats-all.csv", "r", encoding="utf-8") as file:
	csvFile = csv.reader(file)
	for team in csvFile:
		team_banner = banner
		team_banner = team_banner.replace("{University}", team[0])
		team_banner = team_banner.replace("{TeamName}", team[1])
		team_banner = team_banner.replace("{Contestants}", ", ".join(team[2:5]))
		team_pos = team[5]
		team_pos = team_pos[0] + team_pos[1:].rjust(2, '0')
		banner_name = team_pos + ".svg"
		with open(out_pos / banner_name, mode="w", encoding="utf-8") as b:
			b.write(team_banner)
