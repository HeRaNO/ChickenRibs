#include <stdio.h>
#include <string.h>

int max(int a,int b){return a>b?a:b;}

int main()
{
	int i,n;char s[100];
	puts("Enter full name of a file:");printf("The extension is: ");
	scanf("%s",s);n=strlen(s);
	for (i=n-1;~i;i--) if (s[i]=='.') break;
	if (s[max(i,0)]!='.') return 0;
	for (++i;i<n;i++) putchar(s[i]);putchar('\n');
	return 0;
}
