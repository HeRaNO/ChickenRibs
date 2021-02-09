#include <stdio.h>

int main()
{
	double s;
	printf("Enter Frahrenheit temperatur:\n");
	scanf("%lf",&s);
	printf("Celsius equivalent: %.1lf\n",5.0*(s-32)/9.0);
	return 0;
}
