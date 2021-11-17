import os, sys, getopt, shutil
from pathlib import Path

opts, args = getopt.getopt(sys.argv[1:], '', ['sources=', 'problem='])

sourcePath = 'sources'
outputPath = 'output'
problemName = []
extensions = ['.c', '.cpp', '.pas']
acceptName = []

for opt, val in opts:
	if opt == '--sources':
		sourcePath = val
	if opt == '--problem':
		problemName.append(val)

for problem in problemName:
	for extension in extensions:
		acceptName.append(problem + extension)

if not os.path.exists(outputPath):
	os.mkdir(outputPath)

for problem in problemName:
	outputProblemPath = os.path.join(outputPath, problem)
	if not os.path.exists(outputProblemPath):
		os.makedirs(outputProblemPath)

p = Path(sourcePath)

for constant in p.iterdir():
	if not constant.is_dir():
		continue
	for constantFile in constant.iterdir():
		if not constantFile.is_file():
			continue
		if constantFile.name not in acceptName:
			continue
		pName, ext = os.path.splitext(constantFile.name)
		assert pName in problemName
		assert ext in extensions
		newFileName = constant.name + ext
		copyPath = outputPath
		copyPath = os.path.join(copyPath, pName)
		copyPath = os.path.join(copyPath, newFileName)
		shutil.copy(constantFile, copyPath)
