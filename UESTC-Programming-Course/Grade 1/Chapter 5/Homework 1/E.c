#include <stdio.h>

int main()
{
	int a;
	puts("Please input air quality index:");
	scanf("%d",&a);
	if (a<=50) puts("best");
	else if (a<=100) puts("good");
	else if (a<=150) puts("polluted I");
	else if (a<=200) puts("polluted II");
	else if (a<=300) puts("polluted III");
	else puts("polluted IV");
	return 0;
}
