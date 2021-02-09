#include <ctype.h>
#include <stdio.h>

int filter(char str[])
{
	int i,cnt=0;
	for (i=0;str[i]>=32;i++) if (isalpha(str[i])) ++cnt;
	return cnt;
}

int main()
{
	puts("Pls input a sentence: ");
	char s[55];int i;
	fgets(s,55,stdin);
	printf("total letters: %d\nafter filter: ",filter(s));
	for (i=0;s[i]>=32;i++) if (isalpha(s[i])) putchar(s[i]);
	putchar('\n');
	return 0;
}
