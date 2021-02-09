#include <stdio.h>

int main()
{
	puts("Enter numerical grade: ");
	int x;scanf("%d",&x);
	if (x<0||x>100)
	{
		puts("Error");
		return 0;
	}
	x/=10;printf("Letter grade: ");
	switch (x)
	{
		case 10:
		case  9:puts("A");break;
		case  8:puts("B");break;
		case  7:puts("C");break;
		case  6:puts("D");break;
		default:puts("F");break;
	}
	return 0;
}
