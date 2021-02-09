#include <stdio.h>

int main()
{
	int a=0,b=0;char c;
	puts("Enter a sentence:");
	while ((c=getchar())!=EOF)
	{
		if (c<32) break;++b;
		if (c==' ') ++a;
	}
	printf("letters:%d\nspaces:%d\n",b,a);
	return 0;
}
