#include <stdio.h>

char s[1000000],c;
int n,i;

int main()
{
	printf("Enter a message: Reversal is: ");
	while (1)
	{
		c=getchar();
		if (c<32) break;
		s[n++]=c;
	}
	for (i=n-1;~i;i--) putchar(s[i]);putchar('\n');
	return 0;
}