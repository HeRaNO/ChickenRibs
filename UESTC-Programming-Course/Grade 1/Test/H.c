#include <stdio.h>

int main()
{
	int i,x,mx=0;int a[10]={0};
	puts("Please input some non-negative integers (0 to terminate): ");
	while (~scanf("%d",&x))
	{
		if (!x) break;
		while (x){++a[x%10];x/=10;}
	}
	for (i=0;i<=9;i++) if (mx<a[i]) mx=a[i];
	printf("%d:",mx);
	for (i=0;i<=9;i++) if (a[i]==mx) printf("       %d",i);
	puts("");
	return 0;
}