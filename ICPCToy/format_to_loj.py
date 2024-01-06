# ioi-germany/cms format to human-friendly format
from os import listdir, path, mkdir
from shutil import copy
import json

case_root_path = path.join('.', 'cases_by_hash')
subtask_root_path = path.join('.', 'subtasks')
data_root_path = path.join('.', 'data')

if not path.exists(data_root_path):
	mkdir(data_root_path)

def read_hash_value(file_path):
	with open(file_path, 'r') as f:
		line = f.read()
		return line.split('/')[-1]

def analyze_cases(root_path):
	hash_name_map = {}
	all_case = []
	for case in listdir(root_path):
		case_num = case.split('_')[1]
		all_case.append(int(case_num))
	all_case.sort()
	for case in all_case:
		hash_value = read_hash_value(path.join(root_path, f'Case_{case}'))
		hash_name_map[hash_value] = str(case)
	return hash_name_map

def analyze_subtasks(root_path):
	hash_name_map = {}
	all_info = {}
	for subtask in listdir(root_path):
		subtask_path = path.join(root_path, subtask)
		subtask_num = subtask.split('_')[1]
		subtask_info = {}
		for group in listdir(subtask_path):
			group_path = path.join(subtask_path, group)
			group_num = group.split('_')[1]
			cases = analyze_cases(group_path)
			all_cases = []
			for hash_value, case in cases.items():
				name = hash_name_map.get(hash_value)
				if name is None:
					name = f's{subtask_num}g{group_num}_{case}'
					hash_name_map[hash_value] = name
				all_cases.append(name)
			subtask_info[group_num] = all_cases
		all_info[subtask_num] = subtask_info
	return all_info, hash_name_map

all_info, hash_name_map = analyze_subtasks(subtask_root_path)
print(json.dumps(all_info, sort_keys=True, indent=4))

for hash_value, new_file_name in hash_name_map.items():
	src_path = path.join(case_root_path, hash_value, 'in.txt')
	dst_path = path.join(data_root_path, f'{new_file_name}.in')
	copy(src_path, dst_path)
	try:
		src_path = path.join(case_root_path, hash_value, 'out.txt')
		dst_path = path.join(data_root_path, f'{new_file_name}.out')
		copy(src_path, dst_path)
	except Exception as e:
		pass
