#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct{
	unsigned short date;
	char message[80];
}reminder;

reminder a[6],m;

bool cmp(reminder a,reminder b)
{
	if (a.date!=b.date) return a.date>b.date;
	return strcmp(a.message,b.message)>0;
}

void read_line(char s[],int lim)
{
	char ch;int i=0;
	while ((ch=getchar())<32);
	while ((ch=getchar())>=32&&i<lim) s[i++]=ch;
	s[i]='\0';
	return ;
}

int main()
{
	int n=0,i,j;
	while (true)
	{
		if (n==6)
		{
			puts("--No space left!--");
			break;
		}
		puts("Enter day and reminder:");
		scanf("%hu",&m.date);
		if (!m.date) break;
		read_line(m.message,80);
		a[++n]=m;
	}
	for (i=1;i<=n;i++)
		for (j=1;j<i;j++)
			if (cmp(a[j],a[i]))
			{
				m=a[j];a[j]=a[i];a[i]=m;
			}
	printf("Day Reminder\n");
	for (i=1;i<=n;i++) printf("%3u %s\n",a[i].date,a[i].message);
	return 0;
}
