#include <stdio.h>

int main()
{
	puts("Enter the upper bound:");
	int n,i;scanf("%d",&n);
	for (i=2;i*i<=n;i+=2) printf("%d\n",i*i);
	return 0;
}
