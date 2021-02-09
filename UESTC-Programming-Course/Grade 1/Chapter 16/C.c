#include <stdio.h>

typedef struct {
	int id,num;
	char name[25];
}part;

part a[100];
int n;

void read_line(char s[],int lim)
{
	char ch;int i=0;
	while ((ch=getchar())<32);s[i++]=ch;
	while ((ch=getchar())>=32&&i<lim) s[i++]=ch;
	s[i]='\0';
	return ;
}

void insert()
{
	puts("Enter part number: ");scanf("%d",&a[++n].id);
	puts("Enter part name: ");read_line(a[n].name,25);
	puts("Enter quantity on hand: ");scanf("%d",&a[n].num);
	puts("");return ;
}

void search()
{
	int p,i;
	puts("Enter part number: ");scanf("%d",&p);
	for (i=1;i<=n;i++)
		if (a[i].id==p)
		{
			printf("Part name: %s\n",a[i].name);
			printf("Quantity on hand: %d\n",a[i].num);
			return ;
		}
	puts("Part not found.");
	puts("");return ;
}

void update()
{
	int p,i;
	puts("Enter part number: ");scanf("%d",&p);
	for (i=1;i<=n;i++)
		if (a[i].id==p)
		{
			puts("Enter change in quantity on hand: ");scanf("%d",&p);
			a[i].num+=p;return ;
		}
	puts("Part not found.");
	puts("");return ;
}

void output()
{
	int i;
	puts("Part Number   Part Name        Quantity on Hand");
	for (i=1;i<=n;i++)
		printf("%7d       %-30s%d\n",a[i].id,a[i].name,a[i].num);
	puts("");return ;
}

int main()
{
	while (1)
	{
		char a[3];
		puts("Enter operation code: ");
		scanf("%s",a);
		switch (a[0])
		{
			case 'i': insert();break;
			case 's': search();break;
			case 'u': update();break;
			case 'p': output();break;
			case 'q': return 0;
			default : puts("Illegal code");break;
		}
	}
	return 0;
}