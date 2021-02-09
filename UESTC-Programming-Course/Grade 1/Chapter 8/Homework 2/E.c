#include <stdio.h>
#include <string.h>

int main()
{
	char a[100],b[100];int n,i;
	puts("Enter a first and last name: ");
	scanf("%s",a);scanf("%s",b);
	n=strlen(b);
	printf("You entered the name: ");
	for (i=0;i<n;i++) putchar(b[i]);
	putchar(',');putchar(' ');putchar(a[0]);putchar('.');
	return 0;
}
