#include <stdio.h>
#include <string.h>

int main()
{
	int n,i,f=0,cnt[10];char s[100];
	for (i=0;i<10;i++) cnt[i]=0;
	puts("Enter a number:");
	scanf("%s",s);n=strlen(s);
	for (i=0;i<n;i++) ++cnt[s[i]-'0'];
	puts("Repeated digits:");
	for (i=0;i<=9;i++)
		if (cnt[i]>=2)
		{
			f=1;
			printf("%d       %d\n",i,cnt[i]);
		}
	if (!f) puts("No Repeated Digits");
	return 0;
}
