#include <stdio.h>
#include <string.h>

int main()
{
	int n,i;char s[100];
	puts("Enter message: ");
	gets(s);n=strlen(s);
	for (i=0;i<n;i++)
	{
		if (s[i]>='a'&&s[i]<='z') s[i]-=32;
		switch (s[i])
		{
			case 'A':s[i]='4';break;
			case 'B':s[i]='8';break;
			case 'E':s[i]='3';break;
			case 'I':s[i]='1';break;
			case 'O':s[i]='0';break;
			case 'S':s[i]='5';break;
		}
	}
	printf("In B1FF-speak: ");
	for (i=0;i<n;i++) putchar(s[i]);
	for (i=0;i<10;i++) putchar('!');
	putchar('\n');
	return 0;
}
