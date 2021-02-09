#include <stdio.h>

int main()
{
	printf("1");int i,j;
	for (i=2;i<=9;i++) printf("%4d",i);
	puts("");
	printf("-");
	for (i=2;i<=9;i++) printf("   -");
	puts("");
	for (i=1;i<=9;i++)
	{
		for (j=1;j<=i;j++) printf("%-4d",j*i);
		puts("");
	}
	return 0;
}
