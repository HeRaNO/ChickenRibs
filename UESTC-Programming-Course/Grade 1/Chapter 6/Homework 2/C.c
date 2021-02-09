#include <stdio.h>

int main()
{
	float n,x;
	while (~scanf("%f",&n))
	{
		puts("Enter value of trade: ");
		if (n==0.0f) break;
		printf("Commission: $");
		if (n<2500.0f) x=n*0.017f+30.0f;
		else if (n<6250.0f) x=n*0.0066f+56.0f;
		else if (n<20000.0f) x=n*0.0034f+76.0f;
		else if (n<50000.0f) x=n*0.0022f+100.0f;
		else if (n<500000.0f) x=n*0.0011f+155.0f;
		else x=n*0.0009f+255.0f;
		if (x<39.00f) x=39.00f;
		printf("%.2f\n",x);
	}
	return 0;
}
