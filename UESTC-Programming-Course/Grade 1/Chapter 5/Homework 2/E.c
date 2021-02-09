#include <stdio.h>

int main()
{
	int y1,m1,d1,y2,m2,d2;
	puts("Enter first date (mm/dd/yy):");
	scanf("%d/%d/%d",&m1,&d1,&y1);
	puts("Enter second date (mm/dd/yy):");
	scanf("%d/%d/%d",&m2,&d2,&y2);
	if (y1<y2||(y1==y2&&m1<m2)||(y1==y2&&m1==m2&&d1<d2))
		printf("%d/%d/%02d is earlier than %d/%d/%02d\n",m1,d1,y1,m2,d2,y2);
	else
		printf("%d/%d/%02d is earlier than %d/%d/%02d\n",m2,d2,y2,m1,d1,y1);
	return 0;
}
