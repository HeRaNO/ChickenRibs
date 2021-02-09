#include <stdio.h>

int main()
{
	puts("Please input a line of string:");
	char c;
	while ((c=getchar())!=EOF)
	{
		if (c>='0'&&c<='9') continue;
		putchar(c);
	}
	return 0;
}
