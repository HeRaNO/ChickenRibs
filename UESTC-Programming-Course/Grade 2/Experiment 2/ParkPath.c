#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 200
#define MAXL 100

typedef struct TrieTree {
	int id;
	struct TrieTree* nxt[26];
}Trie;

typedef struct Record {
	int len;
	int path[MAXN];
}Rec;

Trie *tree;
Rec rec[MAXN * (MAXN - 1) / 2];
int n, dis[MAXN][MAXN], path[MAXN][MAXN], pt[MAXN][MAXN];
char from[MAXL], to[MAXL], name[MAXN][MAXL];
FILE *fp;

void preWork()
{
	int i;
	tree = (Trie*)malloc(sizeof(Trie));
	tree -> id = 0;
	for (i = 0; i < 26; i++) tree -> nxt[i] = NULL;
	return ;
}

int add(char S[])
{
	int i, j;
	Trie* now = tree;
	for (i = 0; S[i]; i++)
	{
		if (now -> nxt[S[i] - 'a'] == NULL)
		{
			now -> nxt[S[i] - 'a'] = (Trie*)malloc(sizeof(Trie));
			if (now -> nxt[S[i] - 'a'] == NULL)
				return 0;
			for (j = 0; j < 26; j++) now -> nxt[S[i] - 'a'] -> nxt[j] = NULL;
			now -> nxt[S[i] - 'a'] -> id = 0;
		}
		now = now -> nxt[S[i] - 'a'];
	}
	now -> id = n;
	return 1;
}

int query(char S[])
{
	int i;
	Trie* now = tree;
	for (i = 0; S[i]; i++)
	{
		if (now -> nxt[S[i] - 'a'] == NULL) return 0;
		now = now -> nxt[S[i] - 'a'];
	}
	return now -> id;
}

int min(int a, int b)
{
	return a < b ? a : b;
}

void getMap()
{
	fp = fopen("dis.dat", "w");
	memset(dis, 0x3f, sizeof dis);
	int i, u, v, w;
	puts("Pls input the two spots' name (no space, lower case) and the distance (integer).");
	puts("Press Ctrl-Z to end.");
	while (1)
	{
		if (scanf("%s %s %d", from, to, &w) == -1) break;
		fprintf(fp, "%s %s %d\n", from, to, w);
		u = query(from);
		if (!u)
		{
			u = ++n;
			strcpy(name[n], from);
			if (!add(from))
			{
				puts("No memory to allocate.");
				exit(0);
			}
		}
		v = query(to);
		if (!v)
		{
			v = ++n;
			strcpy(name[n], to);
			if (!add(to))
			{
				puts("No memory to allocate.");
				exit(0);
			}
		}
		dis[u][v] = dis[v][u] = min(dis[u][v], w);
	}
	for (i = 1; i <= n; i++) dis[i][i] = 0;
	puts("Map builds successfully");
	fclose(fp);
	return ;
}

void Floyd()
{
	int i, j, k;
	for (i = 1; i <= n; i++)
		for (j = 1; j <=n; j++)
			if (i != j && dis[i][j] != 0x3f3f3f3f)
				path[i][j] = i;
	for (k = 1; k <= n; k++)
		for (i = 1; i <= n; i++)
			for (j = 1; j <= n; j++)
				if (dis[i][j] > dis[i][k] + dis[k][j])
				{
					dis[i][j] = dis[i][k] + dis[k][j];
					path[i][j] = path[k][j];
				}
	puts("The shortest path calculate finished.");
	return ;
}

void getPath()
{
	fp = fopen("AllPath.dat", "w");
	int i, j, k;
	Rec tmp;
	for (i = 1; i <= n; i++)
		for (j = i + 1; j <= n; j++)
		{
			tmp.path[0] = 0;
			fprintf(fp, "%d", dis[i][j]);
			k = j;
			while (k != i)
			{
				tmp.path[++tmp.path[0]] = k;
				k = path[i][k];
			}
			fprintf(fp, " %d %d", tmp.path[0] + 1, i);
			for (k = tmp.path[0]; k; k--)
				fprintf(fp, " %d", tmp.path[k]);
			fputc('\n', fp);
		}
	puts("Paths are saved to AllPath.dat.");
	fclose(fp);
	return ;
}

void processQuery()
{
	fp = fopen("AllPath.dat", "r");
	int i, j, k, u, v;
	for (i = 1; i <= n; i++)
		for (j = i + 1; j <= n; j++)
		{
			fscanf(fp, "%d %d", &rec[u].len, &rec[u].path[0]);
			for (k = 1; k <= rec[u].path[0]; k++)
				fscanf(fp, "%d", &rec[u].path[k]);
			pt[i][j] = u++;
		}
	fclose(fp);
	puts("Now input your queries. Two spots' name in one line.");
	puts("Press Ctrl-Z to end");
	while (1)
	{
		if (scanf("%s %s", from, to) != 2) break;
		u = query(from);
		if (!u)
		{
			puts("The departure isn't appeared in the map!");
			continue;
		}
		v = query(to);
		if (!v)
		{
			puts("The destination isn't appeared in the map!");
			continue;
		}
		if (u > v)
		{
			i = u; u = v; v = i;
		}
		else if (u == v)
		{
			puts("The two spots are same.");
			continue;
		}
		u = pt[u][v];
		printf("The shortest path from %s to %s is:\n", from, to);
		printf("%s", name[rec[u].path[1]]);
		for (i = 2; i <= rec[u].path[0]; i++)
			printf(" <-> %s", name[rec[u].path[i]]);
		printf("\nThe length is: %d\n", rec[u].len);
	}
	puts("\nProcess successfully.");
	return ;
}

int main()
{
	preWork();
	getMap();
	Floyd();
	getPath();
	processQuery();
	return 0;
}
