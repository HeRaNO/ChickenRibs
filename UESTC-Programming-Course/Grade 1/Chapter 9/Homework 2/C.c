#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char mp[10][10];
int i,j,x,y,t,q,a[4][2];

void generate_map(char c[10][10])
{
	srand((unsigned int)time(NULL));
	while (i<=25)
	{
		c[x][y]=i+'A';t=0;memset(a,0,sizeof a);
		if (x+1<=9) if (!c[x+1][y]) a[t++][0]=1;
		if (y+1<=9) if (!c[x][y+1]) a[t++][1]=1;
		if (x-1>=0) if (!c[x-1][y]) a[t++][0]=-1;
		if (y-1>=0) if (!c[x][y-1]) a[t++][1]=-1;
		if (!t) break;
		q=rand()%t;
		x+=a[q][0];y+=a[q][1];++i;
	}
}

void print_map(char a[10][10])
{
	for (i=0;i<10;i++)
	{
		for (j=0;j<10;j++)
			printf("%c",a[i][j]?a[i][j]:'.');
		printf("\n");
	}
}

int main()
{
	generate_map(mp);
	print_map(mp);
	return 0;
}
