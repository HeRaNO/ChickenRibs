#include <stdio.h>

int main()
{
	int n,i,j;
	puts("Enter a positive integer:\n");
	scanf("%d",&n);
	puts("The output is:");
	for (i=1;i<=n;i++)
		for (j=1;j<=i;j++)
			printf("%d%c",j,j==i?'\n':' ');
	return 0;
}
