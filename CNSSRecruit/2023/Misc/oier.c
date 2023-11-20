#include <stdio.h>

int main()
{
	freopen("/home/ctf/data/output.out", "r", stdin);
	char ch;
	while ((ch = getchar()) != EOF)
		putchar(ch);
	return 0;
}