#include <stdio.h>

float tax(float x)
{
	if (x<750) return x*0.01f;
	if (x<2250) return 7.5f+(x-750)*0.02f;
	if (x<3750) return 37.5f+(x-2250)*0.03f;
	if (x<5250) return 82.5f+(x-3750)*0.04f;
	if (x<7000) return 142.5f+(x-5250)*0.05f;
	return 230.0f+(x-7000)*0.06f;
}

int main()
{
	float x;
	puts("Enter amount of taxable income: ");
	scanf("%f",&x);
	printf("Tax due: $%.2f\n",tax(x));
	return 0;
}
