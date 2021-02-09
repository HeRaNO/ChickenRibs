#include <stdio.h>

void write(double x)
{
	printf("area is: %.4lf\n",x);
	return ;
}

int main()
{
	int opt;double a,b,c;
	puts("Please choose a shape you want to calculate (triangle 1, rectangle 2, ladder 3, circle 4):\n");
	scanf("%d",&opt);
	if (opt==1)
	{
		puts("Your choice is triangle. Please input the edge_length and height:\n");
		scanf("%lf %lf",&a,&b);
		write(a*b/2.0);
	}
	else if (opt==2)
	{
		puts("Your choice is rectangle. Please input the length and width:\n");
		scanf("%lf %lf",&a,&b);
		write(a*b);
	}
	else if (opt==3)
	{
		puts("Your choice is ladder. Please input the edge_top, edge_bottom, and height: \n");
		scanf("%lf %lf %lf",&a,&b,&c);
		write((a+b)*c/2.0);
	}
	else
	{
		puts("Your choice is circle. Please input the radium: \n");
		float x,pi=3.1415;
		scanf("%f",&x);
		printf("area is: %.4f\n",pi*(x*x));
	}
	return 0;
}
