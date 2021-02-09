#include <stdio.h>

int main()
{
	int y,m,d;
	printf("Enter a date (mm/dd/yyyy):\n");
	scanf("%d/%d/%d",&m,&d,&y);
	printf("You entered the date %d%02d%d\n",y,m,d);
	return 0;
}
