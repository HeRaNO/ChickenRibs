#include <stdio.h>

int main()
{
	float a,ans=0;char o;
	puts("Enter an expression:");
	scanf("%f",&ans);
	while (scanf(" %c%f",&o,&a)==2)
	{
		switch (o)
		{
			case '+':ans+=a;break;
			case '-':ans-=a;break;
			case '*':ans*=a;break;
			case '/':ans/=a;break;
		}
	}
	printf("Value of expression: %g\n",ans);
	return 0;
}
