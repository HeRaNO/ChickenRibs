#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char mp[10][10];
int i,j,x,y,t,q,a[4][2];

int main()
{
	srand(19260817);
	while (i<=25)
	{
		mp[x][y]=i+'A';t=0;memset(a,0,sizeof a);
		if (x+1<=9) if (!mp[x+1][y]) a[t++][0]=1;
		if (y+1<=9) if (!mp[x][y+1]) a[t++][1]=1;
		if (x-1>=0) if (!mp[x-1][y]) a[t++][0]=-1;
		if (y-1>=0) if (!mp[x][y-1]) a[t++][1]=-1;
		if (!t) break;
		q=rand()%t;
		x+=a[q][0];y+=a[q][1];++i;
	}
	for (i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
			printf("%c",mp[i][j]?mp[i][j]:'.');
		printf("\n");
	}
	return 0;
}
