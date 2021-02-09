#include <stdio.h>

int main()
{
	int a,b;
	printf("Enter a 24-hour time: Equivalent 12-hour time: ");
	scanf("%d:%d",&a,&b);
	if (a/12)
	{
		a-=12;if (!a) a=12;
		printf("%d:%02d PM\n",a,b);
	}
	else
	{
		if (!a) a=12;
		printf("%d:%02d AM\n",a,b);
	}
	return 0;
}