#include <stdio.h>

int main()
{
	char ch;int ans=0;
	puts("Enter a sentence:");
	while ((ch=getchar())!=EOF)
	{
		if (ch>='A'&&ch<='Z') ch+=32;
		if (ch=='a'||ch=='e'||ch=='i'||ch=='o'||ch=='u') ++ans;
	}
	printf("Your sentence contains %d vowels.\n",ans);
	return 0;
}
