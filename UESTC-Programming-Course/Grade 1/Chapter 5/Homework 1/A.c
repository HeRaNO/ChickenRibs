#include <stdio.h>
#include <string.h>

int main()
{
	char s[10];
	puts("Enter a number:");
	scanf("%s",s);
	int n=strlen(s);
	printf("The number %s has %d digits\n",s,n);
	return 0;
}
