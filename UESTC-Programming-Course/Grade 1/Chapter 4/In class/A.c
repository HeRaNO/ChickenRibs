#include <math.h>
#include <stdio.h>

int main()
{
	float a,b,c,d;
	printf("Please input the coordinates of two points:\n");
	printf("point 1(x,y): \n");scanf("(%f,%f)",&a,&b);
	printf("point 2(x,y): \n");scanf(" (%f,%f)",&c,&d);
	printf("This distance is: %.4lf\n",sqrtf((a-c)*(a-c)+(b-d)*(b-d)));
	return 0;
}
