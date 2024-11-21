import os
import aiohttp
import asyncio
import aiofiles
import argparse
from getpass import getpass
from base64 import b64decode
from tqdm.asyncio import tqdm

parser = argparse.ArgumentParser(description='Download all submissions from DOMjudge.')
parser.add_argument('url', type=str, help='DOMjudge url. Example: http://localhost/domjudge')
parser.add_argument('cid', type=str, help='Contest ID.')
parser.add_argument('-u', '--username', type=str, default='admin', help='DOMjudge admin username. Default: admin')
args = parser.parse_args()

password = getpass(f'[*] Input the password of user {args.username}: ')

submission_url = f'{args.url}/api/v4/contests/{args.cid}/submissions'
auth_info = aiohttp.BasicAuth(args.username, password)
root_path = 'submissions'

async def get_submissions():
	async with aiohttp.ClientSession() as session:
		async with session.get(submission_url, auth=auth_info) as resp:
			resp.raise_for_status()
			return await resp.json()

async def write_file(file, content):
	async with aiofiles.open(file, mode='wb') as f:
		await f.write(content)

sub_list = asyncio.run(get_submissions())
all_submissions_cnt = len(sub_list)
print(f'{all_submissions_cnt} submission(s) found.')

if not os.path.exists(root_path):
	os.mkdir(root_path)

async def main_downloading():
	async with aiohttp.ClientSession() as session:
		async def download_one(rec):
			sub_id = rec['id']

			code_path = os.path.join(root_path, rec['problem_id'])
			if not os.path.exists(code_path):
				os.mkdir(code_path)

			file_url = f'{submission_url}/{sub_id}/source-code'
			async with session.get(file_url, auth=auth_info) as resp:
				resp.raise_for_status()
				files = await resp.json()

			file = files[0]
			file_name = '-'.join([rec['team_id'], sub_id, file['filename']])
			file_path = os.path.join(code_path, file_name)
			await write_file(file_path, b64decode(file['source']))

		tasks = [download_one(rec) for rec in sub_list]
		await tqdm.gather(*tasks)

asyncio.run(main_downloading())
