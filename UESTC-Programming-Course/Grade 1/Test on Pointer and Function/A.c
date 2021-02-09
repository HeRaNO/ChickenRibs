#include <stdio.h>
#define N 10

void find_two_largest(int a[],int **max,int **max2,int *num,int *num2){
	int i;
	if (a[0]>a[1]){*max=&a[0];*num=0;*max2=&a[1];*num2=1;}
	else {*max=&a[1];*num=1;*max2=&a[0];*num2=0;}
	for (i=2;i<N;i++)
	{
		if (a[i]>**max)
		{
			*max2=*max;*num2=*num;
			*max=&a[i];*num=i;
		}
		else if (a[i]>**max2){*max2=&a[i];*num2=i;}
	}
	return ;
}

int main()
{
	int a[N],*p,*max,*max2,num,num2;

	printf("Please input 10 integers: \n");
	for(p=a;p<a+N;p++){
		scanf("%d",p);
	}
	find_two_largest(a,&max,&max2,&num,&num2);
	printf("The largest: %d\nThe index of the largest: %d\n"
	"The second largest: %d\n"
	"The index of the second largest: %d\n",*max,num,*max2,num2);
	return 0;
}
