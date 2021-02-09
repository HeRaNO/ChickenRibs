#include <stdio.h>

int main()
{
	puts("Enter a sentence: ");
	char ch;int nl=0,n=0;
	while (1)
	{
		ch=getchar();
		if (ch<32){++n;break;}
		if (ch==' ') ++n;
		else ++nl;
	}
	printf("Average word length: %.1f\n",(float)nl/(float)n);
	return 0;
}
