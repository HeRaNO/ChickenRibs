#include <stdio.h>

int judge(char c)
{
	if (c>='A'&&c<='Z') return c-'A'+1;
	if (c>='a'&&c<='z') return c-'a'+1;
	return -1;
}

int main()
{
	char c;int x;
	puts("Please input a line of characters:");
	while (1)
	{
		c=getchar();
		if (c<32) break;
		x=judge(c);
		if (!~x) puts("This character is not a letter.");
		else printf("The location of %c is: %d\n",c,x);
	}
	return 0;
}
