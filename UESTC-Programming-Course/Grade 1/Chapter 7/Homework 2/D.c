#include <stdio.h>

int main()
{
	puts("Enter a first name and last name:");
	char f,c;
	while (1)
	{
		c=getchar();
		if (c!=' ') break;
	}
	f=c;
	while (1)
	{
		c=getchar();
		if (c==' ') break;
	}
	while (1)
	{
		c=getchar();
		if (c<32) break;
		putchar(c);
	}
	putchar(' ');putchar(f);putchar('.');putchar('\n');
	return 0;
}
