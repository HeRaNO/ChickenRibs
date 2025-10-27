import asyncio
import subprocess
from base64 import b64encode
import json

with open("monitor.json") as f:
	all_ips = json.loads(f.read())

async def run_command(ip, seat):
	# proc = await asyncio.create_subprocess_exec("scp",
	# 	"-i", "~/.ssh/private_key", "-o", "StrictHostKeyChecking no",
	# 	"/home/icpcweb/ContestInstructions(zh).pdf",
	# 	f"root@{ip}:/home/team/Desktop",
	# 	stdout=asyncio.subprocess.PIPE,
	# 	stderr=asyncio.subprocess.PIPE)
	cmd = "ls ~"
	proc = await asyncio.create_subprocess_exec("ssh",
		"-i", "~/.ssh/private_key", "-o", "StrictHostKeyChecking no",
		f"root@{ip}", f"echo $(echo {b64encode(cmd.encode()).decode()} | base64 -d | bash)",
		stdout=asyncio.subprocess.PIPE,
		stderr=asyncio.subprocess.PIPE)
	stdout, stderr = await proc.communicate()
	return f"seat: {seat}, stdout:\n{stdout.decode()}\n\nstderr:\n{stderr.decode()}\n----------------------\n"

async def main():
	tasks = []
	for _, op in all_ips["monitors"].items():
		tasks.append(run_command(op["ip"], op["hostname"]))
	res = await asyncio.gather(*tasks)
	for r in res:
		print(r)

asyncio.run(main())
