#include <stdio.h>

int main()
{
	char s[1000];int n=0,i,x;
	puts("Enter message to be encrypted: ");
	while (1)
	{
		s[n]=getchar();
		if (s[n]=='!'||s[n]=='?'||s[n]=='.') break;
		++n;
	}
	puts("Enter shift amount (1-25): ");
	scanf("%d",&x);
	printf("Encrypted message: ");
	for (i=0;i<=n;i++)
	{
		if (s[i]>='A'&&s[i]<='Z')
		{
			int t=s[i];
			t=((t-65)+x)%26;
			s[i]=t+'A';
		}
		else if (s[i]>='a'&&s[i]<='z')
		{
			int t=s[i];
			t=((t-97)+x)%26;
			s[i]=t+'a';
		}
		putchar(s[i]);
	}
	putchar('\n');
	return 0;
}
