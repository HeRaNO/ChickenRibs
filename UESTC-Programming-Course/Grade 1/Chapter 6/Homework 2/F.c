#include <stdio.h>

int a[7][8];

int main()
{
	int n,x,pt=0,w=2,i,j;
	puts("Enter number of days in month:");
	scanf("%d",&n);
	puts("Enter starting day of the week (1=Sun, 7=Sat):");
	scanf("%d",&x);
	for (i=x;i<=7;i++) a[1][i]=++pt;
	i=1;++pt;
	while (pt<=n)
	{
		a[w][i++]=pt++;
		if (i==8)
		{
			++w;i=1;
		}
	}
	for (i=1;i<=w;i++)
	{
		for (j=1;j<=7;j++)
		{
			if (!a[i][j]) printf("   ");
			else printf("%3d",a[i][j]);
		}
		puts("");
	}
	return 0;
}
