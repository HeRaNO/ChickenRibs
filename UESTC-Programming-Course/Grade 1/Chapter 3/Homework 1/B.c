#include <stdio.h>

int main()
{
	printf("Please input your height (meter): \n");
	float a;scanf("%f",&a);
	printf("Your height in inch is: %.4f inches\n",a*100.0f/2.54f);
	return 0;
}
