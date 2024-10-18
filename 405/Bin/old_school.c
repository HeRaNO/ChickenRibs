#include <stdio.h>
#include <stdlib.h>

int res[50] = {221, 96, 50, 137, 220, 206, 182, 65, 139, 105, 198, 55, 78, 59, 67, 235, 44, 84, 254, 6, 245, 220, 180, 6, 159, 14, 209, 23};

int main(int argc, char const *argv[])
{
	srand(0);
	for (int i = 0; i <= 10000; ++i )
	{
		char v4 = rand();
		int v5 = rand();
		res[v5 % 27] ^= v4;
	}
	for (int i = 0; i <= 26; i++)
		putchar(res[i]);
	return 0;
}
