#include <stdio.h>

int main()
{
	int i;
	unsigned long long ID,IDmx=0;float sc,scmx=-1.0;
	for (i=1;i<=5;i++)
	{
		scanf("%llu %f",&ID,&sc);
		if (scmx<sc)
		{
			scmx=sc;IDmx=ID;
		}
	}
	printf("Student Number: %llu\nmaxScore: %d\n", IDmx, (int)scmx);
	return 0;
}
