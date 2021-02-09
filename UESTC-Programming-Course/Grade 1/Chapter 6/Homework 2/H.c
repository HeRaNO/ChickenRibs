#include <stdio.h>
/*
	#include <string.h>
	#include <stdbool.h>
*/

/*bool a[10];*/

int main()
{
	/*puts("94185");*/
	int i;bool f;
	for (i=10920;i<=99999;i+=1365)
	{
		int x=i;f=true;memset(a,0,sizeof a);
		while (x&&f)
		{
			if (a[x%10]){f=false;break;}
			a[x%10]=true;x/=10;
		}
		if (f) printf("%d\n",i);
	}
	return 0;
}
