#include <stdio.h>

int main()
{
	int a;
	puts("Please input age: ");
	scanf("%d",&a);
	if (a>59)
	{
		int s;
		puts("Please input status: ");
		scanf("%d",&s);
		if (!s) puts("Retired senior");
		else puts("Working senior");
	}
	else
	{
		if (a>20) puts("Adult");
		else if (a>12) puts("Teen");
		else puts("Child");
	}
	return 0;
}
