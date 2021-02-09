#include <stdio.h>

int main()
{
	char s[1000];int n=0,l,r,i,f=1;
	puts("Enter a sentence: ");
	while (1)
	{
		s[n]=getchar();
		if (s[n]=='!'||s[n]=='?'||s[n]=='.') break;
		++n;
	}
	printf("Reversal of sentence: ");
	--n;l=r=n;
	while (r>=0)
	{
		if (f) f=0;
		else putchar(' ');
		while (s[l]!=' '&&l>=0) --l;
		++l;
		for (i=l;i<=r;i++) putchar(s[i]);
		l-=2;r=l;
	}
	putchar(s[n+1]);putchar('\n');
	return 0;
}
