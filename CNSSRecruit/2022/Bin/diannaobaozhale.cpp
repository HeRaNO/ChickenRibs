#include <cstdio>

int main()
{
	putchar('c');
	putchar('n');
	putchar('s');
	putchar('s');
	putchar('{');
	char rbpvar5 = 'c';
	for (int i = 0; i <= 9; i++)
	{
		putchar(rbpvar5);
		rbpvar5 += 2; rbpvar5 ^= 1;
	}
	putchar('}');
	putchar('\n');
	return 0;
}