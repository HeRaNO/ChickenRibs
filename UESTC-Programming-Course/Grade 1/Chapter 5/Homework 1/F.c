#include <stdio.h>

int main()
{
	float a,b;
	puts("Please input coordinates of a point (x,y): ");
	scanf("(%f,%f)",&a,&b);
	if (a==0||b==0)
	{
		if (a!=0) puts("This point is on the x-axis.");
		else if (b!=0) puts("This point is on the y-axis.");
		else puts("This point is the origin.");
		return 0;
	}
	if (a>0)
	{
		if (b>0) puts("This point is in QI.");
		else puts("This point is in QIV.");
	}
	else
	{
		if (b>0) puts("This point is in QII.");
		else puts("This point is in QIII.");
	}
	return 0;
}
