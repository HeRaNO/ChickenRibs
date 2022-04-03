import sys
import time
import json
import requests
import markdown
from bs4 import BeautifulSoup

session = requests.Session()

dataFields = ['constraints', 'content', 'note', 'standardInput', 'standardOutput']

url = '' # fill in the graphql request url

def queryMaxPage():
	queryPage = 'query ProblemListGQL($page: Int!, $filter: String) {\n  problemList(page: $page, filter: $filter) {\n    maxPage\n    __typename\n  }\n}\n'

	data = {
		'operationName': 'ProblemListGQL',
		'query': queryPage,
		'variables': {
			'page': 1,
			'filter': ''
		}
	}

	r = session.post(url, json = data)
	resp = r.json()
	dataField = resp.get('data')
	if dataField is None:
		print(resp)
		raise Exception('cannot find data field')
	dataField = dataField.get('problemList')
	if dataField is None:
		print(resp)
		raise Exception('cannot find problemList field')
	maxPage = dataField.get('maxPage')
	if maxPage is None:
		print(resp)
		raise Exception('cannot find maxPage field')
	return maxPage

def queryProblemSlugOnPage(page):
	query = 'query ProblemListGQL($page: Int!, $filter: String) {\n  problemList(page: $page, filter: $filter) {\n    problemList {\n      slug\n      __typename\n    }\n    __typename\n  }\n}\n'
	data = {
		'operationName': 'ProblemListGQL',
		'query': query,
		'variables': {
			'page': page,
			'filter': ''
		}
	}
	r = session.post(url, json = data)
	resp = r.json()
	dataField = resp.get('data')
	if dataField is None:
		print(resp)
		raise Exception('cannot find data field')
	dataField = dataField.get('problemList')
	if dataField is None:
		print(resp)
		raise Exception('cannot find problemList field')
	dataField = dataField.get('problemList')
	if dataField is None:
		print(resp)
		raise Exception('cannot find problemList field')
	return [data.get('slug') for data in dataField]

def getImgs(data, field):
	content = data.get(field)
	if content is None:
		print(data)
		raise Exception('cannot find ' + field + ' field')
	html = markdown.markdown(content)
	soup = BeautifulSoup(html, 'html.parser')
	imgs = soup.findAll('img')
	return [img.get('src') for img in imgs]

def getImgsInProblem(slug):
	query = 'query ProblemDetailGQL($slug: String!) {\n  problem(slug: $slug) {\n    content\n    standardInput\n    standardOutput\n    constraints\n    note\n      __typename\n    }\n    __typename\n  \n}\n'
	data = {
		'operationName': 'ProblemDetailGQL',
		'query': query,
		'variables': {
			'slug': slug
		}
	}
	r = session.post(url, json = data)
	resp = r.json()
	dataField = resp.get('data')
	if dataField is None:
		print(resp)
		raise Exception('cannot find data field')
	dataField = dataField.get('problem')
	if dataField is None:
		print(resp)
		raise Exception('cannot find problem field')
	for field in dataFields:
		imgs = getImgs(dataField, field)
		for img in imgs:
			print(slug, img)

maxPage = queryMaxPage()

for i in range(maxPage):
	print('page', i + 1, 'start', file=sys.stderr)
	slugs = queryProblemSlugOnPage(i + 1)
	for slug in slugs:
		print(slug, 'start', file=sys.stderr)
		getImgsInProblem(slug)
		print(slug, 'finished', file=sys.stderr)
		time.sleep(1) # for anti crawl
	print('page', i + 1, 'finished', file=sys.stderr)
