#include <stdio.h>

int main()
{
	puts("Enter number of fibonacci numbers: ");
	printf("Fibonacci numbers: ");
	int n,i;long long f[51];
	scanf("%d",&n);
	f[0]=0LL;f[1]=1LL;
	for (i=2;i<n;i++) f[i]=f[i-1]+f[i-2];
	printf("%lld",f[0]);
	for (i=1;i<n;i++) printf(" ,%lld",f[i]);
	putchar('\n');
	return 0;
}
