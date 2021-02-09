#include <stdio.h>

char a[100000];

int main()
{
	char *p=a,*i,c;
	puts("Enter a message:");printf("Reversal is: ");
	while (1)
	{
		c=getchar();
		if (c<32) break;
		*(p++)=c;
	}
	for (i=p-1;i!=a-1;i--) putchar(*i);putchar('\n');
	return 0;
}
