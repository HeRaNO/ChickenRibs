#include <stdio.h>

int main()
{
	int a;
	printf("Enter a wind speed: ");
	scanf("%d",&a);
	if (a<1) puts("Calm");
	else if (a>=1&&a<=3) puts("Light air");
	else if (a>=4&&a<=27) puts("Breeze");
	else if (a>=28&&a<=47) puts("Gale");
	else if (a>=48&&a<=63) puts("Storm");
	else if (a>63) puts("Hurricane");
	return 0;
}
