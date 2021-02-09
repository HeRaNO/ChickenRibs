#include <stdio.h>

char ch;
int a,b,c,d,o,x,y,t;

int gcd(int a,int b){return !b?a:gcd(b,a%b);}

int main()
{
	puts("Enter two fractions separated by a +, -, * or / sign: ");
	scanf("%d/%d %c %d/%d",&a,&b,&ch,&c,&d);
	switch (ch)
	{
		case '+':o=0;break;
		case '-':o=1;break;
		case '*':o=2;break;
		default:o=3;break;
	}
	if (!o){x=a*d+b*c;y=b*d;}
	else if (o==1){x=a*d-b*c;y=b*d;}
	else if (o==2){x=a*c;y=b*d;}
	else{x=a*d;y=b*c;}
	t=gcd(x,y);x/=t;y/=t;
	printf("The result is %d/%d\n",x,y);
	return 0;
}
