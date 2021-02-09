#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char a[100],b[100];int la,lb,cnt[26]={0},i;
	puts("Enter first word: ");
	scanf("%s",a);la=strlen(a);
	puts("Enter second word: ");
	scanf("%s",b);lb=strlen(b);
	for (i=0;i<la;i++) ++cnt[tolower(a[i])-'a'];
	for (i=0;i<lb;i++) --cnt[tolower(b[i])-'a'];
	for (i=0;i<26;i++) if (cnt[i]) return puts("The words are not anagrams."),0;
	puts("The words are anagrams.");
	return 0;
}
