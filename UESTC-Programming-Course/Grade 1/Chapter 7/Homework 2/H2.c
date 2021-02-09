#include <stdio.h>
#include <string.h>

int main()
{
	puts("Enter a sentence: ");
	char s[100];int nl=0,n=0;
	while (~scanf("%s",s))
	{
		nl+=strlen(s);++n;
	}
	printf("Average word length: %.1f\n",(float)nl/(float)n);
	return 0;
}
