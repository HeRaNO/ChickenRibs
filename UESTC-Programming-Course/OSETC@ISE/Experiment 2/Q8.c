#include <stdio.h>

int a[7][8];

int main()
{
	int n,x,pt=0,w=2,i,j;
	printf("Enter number of days in month: ");
	scanf("%d",&n);
	printf("Enter starting day of the week (1=Sun, 7=Sat): \n");
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
	for (i=1;i<w;i++)
	{
		if (!a[i][1]) printf("  ");
		else printf("%2d",a[i][1]);
		for (j=2;j<=7;j++)
		{
			if (!a[i][j]) printf("   ");
			else printf("%3d",a[i][j]);
		}
		puts("");
	}
	if (!a[w][1]) return 0;
	else printf("%2d",a[w][1]);
	for (j=2;j<=7;j++)
	{
		if (!a[w][j]) break;
		else printf("%3d",a[w][j]);
	}
	puts("");
	return 0;
}
