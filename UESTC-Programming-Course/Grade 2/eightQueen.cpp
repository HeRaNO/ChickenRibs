#include <cstdio>
#define MAXN 21
#define MAXD 41

bool c[MAXN], ld[MAXD], rd[MAXD];
int a[MAXN], cnt, n;

void dfs(int x)
{
	if (x==n+1)
	{
		++cnt; printf("The #%d method: ", cnt);
		for (int i = 1; i <= n; i++) printf("(%d,%d)%c", i, a[i], i==n ? '\n' : ' ');
		return ;
	}
	for (int i = 1; i <= n; i++)
		if (!c[i] && !rd[i+x] && !ld[x-i+n+1])
		{
			c[i] = true; rd[i + x] = true; ld[x - i + n + 1] = true; a[x] = i;
			dfs(x + 1);
			c[i] = false; rd[i + x] = false; ld[x - i + n + 1] = false;
		}
	return ;
}

int main()
{
	printf("Please input n(1-20): ");
	scanf("%d", &n);
	if (n < 1 || n > 20)
	{
		puts("n is out of range [1,20]");
		return 0;
	}
	dfs(1);
	printf("The sum of method(s) is %d.\n", cnt);
	return 0;
}
