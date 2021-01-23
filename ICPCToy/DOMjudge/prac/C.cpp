#include <bits/stdc++.h>
using namespace std;

char s[10];
int T,n;

int main(int argc, char const *argv[])
{
	scanf("%d",&T);
	while (T--)
	{
		scanf("%d",&n);
		if (n==2)
		{
			puts("OUTPUT 0");
			continue;
		}
		for (int i=1;i<n-1;i++)
		{
			printf("READ %d\n",i);
			fflush(stdout);
			scanf("%s",s);
			if (s[0]=='f')
			{
				printf("OUTPUT %d\n",i-1);
				break;
			}
		}
	}
	return 0;
}