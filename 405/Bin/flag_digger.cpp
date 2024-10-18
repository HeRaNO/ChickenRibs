#include <cstdio>
#include <vector>

void dfs(int x, int step, std::vector<int> path, std::vector<std::vector<int>> g, const std::vector<int> &re)
{
	if (re[step] != -1)
		if (x != re[step])
			return ;
	bool f = false;
	for (int i = 0; i < 16; i++)
		if (g[x][i])
		{
			f = true;
			path.push_back(i);
			g[x][i] = g[i][x] = 0;
			dfs(i, step + 1, path, g, re);
			path.pop_back();
			g[x][i] = g[i][x] = 1;
		}
	if (!f && step == 29)
	{
		for (int i : path)
		{
			if (i < 10)
				printf("%d", i);
			else
				printf("%c", i+55);
		}
		puts("");
	}
	return ;
}

int main()
{
	int n = 16, m = 29, k = 11;
	std::vector<std::vector<int>> g(n, std::vector<int>(n));
	for (int i = 0; i < m; i++)
	{
		int a, b; scanf("%d %d", &a, &b);
		g[a][b] = g[b][a] = 1;
	}
	std::vector<int> re(29, -1);
	for (int i = 0; i < k; i++)
	{
		int x, y; scanf("%d %d", &x, &y);
		re[x] = y;
	}
	for (int i = 0; i < 16; i++)
	{
		std::vector<int> path;
		path.push_back(i);
		dfs(i, 0, path, g, re);
	}
	return 0;
}
/*
Input:
0 1
0 3
0 10
0 15
1 2
1 10
1 15
2 11
3 10
3 13
3 15
4 7
4 12
5 6
5 7
5 10
5 13
6 7
7 8
7 9
7 11
8 9
10 11
10 15
11 12
12 13
12 15
13 14
14 15
1 15
4 2
5 11
7 0
12 7
15 12
16 4
18 9
23 10
25 13
28 3
*/
