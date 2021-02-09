#include <stdio.h>

int main()
{
	int a;
	puts("Enter wind speed:");
	scanf("%d",&a);
	if (a<1) puts("The description is: Calm");
	else if (a>=1&&a<=3) puts("The description is: Light air");
	else if (a>=4&&a<=27) puts("The description is: Breeze");
	else if (a>=28&&a<=47) puts("The description is: Gale");
	else if (a>=48&&a<=63) puts("The description is: Storm");
	else if (a>63) puts("The description is: Hurricane");
	return 0;
}
