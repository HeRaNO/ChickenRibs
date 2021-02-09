#include <stdio.h>
#include <string.h>
#define MAXN 20

char s[MAXN];
int a[10],n,i;

int main()
{
	printf("Enter a number: ");
	scanf("%s",s);n=strlen(s);
	for (i=0;i<n;i++) ++a[s[i]-'0'];
	printf("Digit:		0");
	for (i=1;i<=9;i++) printf("%3d",i);putchar('\n');
	printf("Occurrences:	%d",a[0]);
	for (i=1;i<=9;i++) printf("%3d",a[i]);putchar('\n');
	return 0;
}
