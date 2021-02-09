#include <stdio.h>
#include <stdlib.h>

int pt,mn=~(1<<31);
int a[8]={480, 583, 679, 767, 840, 945, 1140, 1305};

int main()
{
	puts("Enter a 24-hour time:");
	int p,q,i;scanf("%d:%d",&p,&q);p=p*60+q;
	for (i=0;i<8;i++)
		if (mn>abs(p-a[i]))
		{
			mn=abs(p-a[i]);pt=i;
		}
	switch (pt)
	{
		case 0:printf("Closest departure time is 8:00 a.m., arriving at 10:16 a.m.\n");break;
		case 1:printf("Closest departure time is 9:43 a.m., arriving at 11:52 a.m.\n");break;
		case 2:printf("Closest departure time is 11:19 a.m., arriving at 1:31 p.m.\n");break;
		case 3:printf("Closest departure time is 12:47 p.m., arriving at 3:00 p.m.\n");break;
		case 4:printf("Closest departure time is 2:00 p.m., arriving at 4:08 p.m.\n");break;
		case 5:printf("Closest departure time is 3:45 p.m., arriving at 5:55 p.m.\n");break;
		case 6:printf("Closest departure time is 7:00 p.m., arriving at 9:20 p.m.\n");break;
		case 7:printf("Closest departure time is 9:45 p.m., arriving at 11:58 p.m.\n");break;
	}
	return 0;
}
