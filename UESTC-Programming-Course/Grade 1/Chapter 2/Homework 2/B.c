#include <stdio.h>

int main()
{
	int s,m,h;
	printf("Please input time in seconds: \n");
	scanf("%d",&s);
	m=s/60;s%=60;h=m/60;m%=60;
	printf("Hours: %d\n",h);
	printf("Minutes: %d\n",m);
	printf("Seconds: %d\n",s);
	return 0;
}
