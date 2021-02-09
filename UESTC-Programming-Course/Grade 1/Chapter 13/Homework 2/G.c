#include <stdio.h>

int main()
{
	char s[1000];
	puts("Enter a domain name:");
	scanf("%s",s);
	printf("The URL is: http://www.%s/index.html\n",s);
	return 0;
}
