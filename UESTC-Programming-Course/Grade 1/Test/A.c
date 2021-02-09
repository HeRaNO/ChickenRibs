#include <stdio.h>

typedef struct {
	char name[100];
	int num,x;
}inventory;

inventory a[100];
int num_part;

void read_line(char a[],int lim)
{
	int i=0;
	char ch=getchar();
	while (ch<32) ch=getchar();
	while (ch>=32&&i<lim-1) a[i++]=ch,ch=getchar();
	a[i++]='\0';return ;
}

void insert()
{
	if (num_part==100)
	{
		puts("Already full!");
		return ;
	}
	puts("Enter part number: ");
	scanf("%d",&a[num_part].num);
	puts("Enter part name: ");
	read_line(a[num_part].name,100);
	puts("Enter quantity on hand: ");
	scanf("%d",&a[num_part].x);
	num_part++;
	return ;
}

void search()
{
	int i,f;
	puts("Enter part number: ");
	scanf("%d",&f);
	for (i=0;i<num_part;i++)
		if (a[i].num==f)
		{
			printf("Part name: %s\n",a[i].name);
			printf("Quantity on hand: %d\n",a[i].x);
			return ;
		}
	puts("Part not found.");
	return ;
}

void update()
{
	int i,f;
	puts("Enter part number: ");
	scanf("%d",&f);
	for (i=0;i<num_part;i++)
		if (a[i].num==f) break;
	if (i==num_part){puts("Part not found.");return ;}
	puts("Enter change in quantity on hand: ");
	scanf("%d",&f);
	a[i].x+=f;
	return ;
}

void print()
{
	int i;
	printf("Part Number   Part Name        Quantity on Hand\n");
	for (i=0;i<num_part;i++) printf("%7d       %-30s%d\n",a[i].num,a[i].name,a[i].x);
	return ;
}

int main()
{
	char opt[3];
	while (1)
	{
		puts("Enter operation code: ");
		scanf("%s",opt);
		switch(opt[0])
		{
			case 'i': insert();break;
			case 's': search();break;
			case 'u':update();break;
			case 'p':print();break;
			case 'q': return 0;
			default: puts("Invaild option");
		}
	}
	return 0;
}