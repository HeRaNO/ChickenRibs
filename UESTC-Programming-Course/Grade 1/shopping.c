#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100
#define MAX_ID_LEN 30
#define MAX_NAME_LEN 30
#define MAX_DISCOUNT_LEN 30

typedef struct {
	char id[MAX_ID_LEN];
	char name[MAX_NAME_LEN];
	char discount[MAX_DISCOUNT_LEN];

	int price;
	int amount;
	int remain;
} Goods;

typedef struct node {
	Goods info;
	struct node *nxt;
} GoodsList;

GoodsList *list = NULL, *list_last = NULL;

char s[180];
int currentCnt = 0;

/**
 ** The way of storage
 	list is the pointer of the first one.
 	list_last is the pointer of the NEXT of the last one. And it is the position which should an new element be inserted.
**/

void readLine(char s[],int lim)
{
	char ch; int i = 0;
	while ((ch = getchar()) < 32)
	{
		if (ch == EOF)
		{
			s[i] = '\0';
			return ;
		}
	}
	s[i++]=ch;
	while ((ch = getchar()) >= 32 && i < lim) s[i++] = ch;
	s[i] = '\0';
	return ;
}

void outputMenu()
{
	puts("*******************************************");
	puts("1. 显示所有商品的信息；");
	puts("2. 修改某个商品的信息；");
	puts("3. 插入某个商品的信息；");
	puts("4. 删除某个商品的信息；");
	puts("5. 查找某个商品的信息；");
	puts("6. 商品存盘并退出系统；");
	puts("7. 对商品价格进行排序；");
	puts("8. （慎用）删除所有内容；");
	puts("其他. 不存盘并退出系统；");
	puts("*******************************************");
	return ;
}

void readAndInitialize(GoodsList **L, GoodsList **LL)
{
	GoodsList *p;

	*L = (GoodsList *)malloc(sizeof(GoodsList));

	p = *L;
	p -> nxt = NULL;

	FILE *fp = fopen("goodsinfo.txt", "r");

	if (fp == NULL)
	{
		printf("商品信息初始化文件不存在！程序将为您新建一个。\n");
		fclose(fp);
		fp = fopen("goodsinfo.txt", "w");
		fclose(fp);
		*LL = p;
		return ;
	}

	while (1)
	{
		if (fgets(s, 180, fp) == NULL) break;
		int i, t = 0;

		for (i = 0; s[i] >= 32; i++) p -> info.id[t++] = s[i];
		p -> info.id[t++] = '\0';t = 0;

		for (i++; s[i] != '\t'; i++) p -> info.name[t++] = s[i];
		p -> info.name[t++] = '\0';t = 0;

		p -> info.price = 0;
		for (i++; s[i] >= 32; i++) p -> info.price = p -> info.price * 10 + s[i] - '0';

		for (i++; s[i] >= 32; i++) p -> info.discount[t++] = s[i];
		p -> info.discount[t++] = '\0';t = 0;

		p -> info.amount = 0;
		for (i++; s[i] >= 32; i++) p -> info.amount = p -> info.amount * 10 + s[i] - '0';

		p -> info.remain = 0;
		for (i++; s[i] >= 32; i++) p -> info.remain = p -> info.remain * 10 + s[i] - '0';

		++currentCnt;

		p -> nxt = (GoodsList *)malloc(sizeof(GoodsList));
		p = p -> nxt;
		p -> nxt = NULL;
	}

	*LL = p;
	printf("商品的链表文件已建立，有 %d 个商品记录。\n",currentCnt);

	fclose(fp);
	return ;
}

void printOneInfo(Goods a)
{
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
	printf("ID：%s\t名称：%s\t价格：%d\t折扣：%s\t数量：%d\t剩余：%d",a.id, a.name, a.price, a.discount, a.amount, a.remain);
	printf("\n++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n"); 
	return ;
}

void printAllInfo(GoodsList *L)
{
	int i;
	for (i = 0; i < currentCnt; i++)
	{
		printOneInfo(L -> info);
		L = L -> nxt;
	}
	return ;
}

void readItem(Goods *a)
{
	puts("输入新的商品信息：");
	printf("商品 ID：");readLine(a -> id, 30);
	printf("商品名称：");readLine(a -> name, 30);
	printf("商品价格：");scanf("%d", &a -> price);
	printf("商品折扣：");readLine(a -> discount, 30);
	printf("商品数量：");scanf("%d", &a -> amount);
	printf("商品剩余：");scanf("%d", &a -> remain);
	return ;
}

void infoChange(GoodsList **L)
{
	int i = 0, f = 0;
	GoodsList *p = *L;

	printf("输入需要修改的商品 ID（-1 退出修改）：");
	readLine(s, 30);

	if (s[0] == '-' && s[1] == '1' && s[2] == '\0') return ;

	while (i < currentCnt)
	{
		if (strcmp(p -> info.id, s) == 0)
		{
			f = 1;
			break;
		}
		p = p -> nxt;
		i++;
	}

	if (!f)
	{
		puts("您要修改的商品不存在！");
		return ;
	}

	readItem(&p -> info);

	puts("修改商品信息成功！修改后的商品为：");
	printOneInfo(p -> info);

	return ;
}

void infoInsert(GoodsList **L, GoodsList **LL)
{
	Goods a; int pos, i;
	readItem(&a);

err:
	printf("输入数字以表示您要插入的商品位置：0. 商品列表尾部 1. 商品列表头部 i. 商品列表中间第 i 号位置：");
	scanf("%d", &pos);

	if (!pos)
	{
		(*LL) -> info = a;
		(*LL) -> nxt = (GoodsList*)malloc(sizeof(GoodsList));
		(*LL) = (*LL) -> nxt;
		(*LL) -> nxt = NULL;
		++currentCnt;
		return ;
	}

	if (pos == 1)
	{
		GoodsList *nHead = (GoodsList*)malloc(sizeof(GoodsList));
		nHead -> info = a;
		nHead -> nxt = *L;
		*L = nHead;
		++currentCnt;
		return ;
	}

	GoodsList *p = *L, *nItem;
	nItem = (GoodsList*)malloc(sizeof(GoodsList));
	nItem -> info = a;
	nItem -> nxt = NULL;

	for (i = 1; i < pos - 1; i++)
	{
		if (p -> nxt == NULL)
		{
			puts("未找到该位置，请重新输入！");
			goto err;
		}
		else p = p -> nxt;
	}

	if (p -> nxt == NULL)
	{
		puts("未找到该位置，请重新输入！");
		goto err;
	}

	nItem -> nxt = p -> nxt;
	p -> nxt = nItem;
	++currentCnt;
	return ;
}

void infoDelete(GoodsList **L)
{
	if (!currentCnt)
	{
		puts("列表中没有商品！");
		return ;
	}

	char opt[3];
	int f = 0;
	GoodsList *p = *L, *q;

	printf("输入需要删除的商品 ID（-1 退出删除）：");
	readLine(s, 30);

	if (s[0] == '-' && s[1] == '1' && s[2] == '\0') return ;

	if (strcmp((*L) -> info.id, s) == 0)
	{
		printOneInfo((*L) -> info);
		puts("是否删除该商品？（Y/N）：");
		scanf("%s", opt);
		if (opt[0] == 'N'||opt[0] == 'n') return ;
		else if (opt[0] == 'Y'||opt[0] == 'y')
		{
			p = p -> nxt;
			free(*L);
			*L = p;
			currentCnt--;
			printf("Tips: 删除 ID 为 %s 的商品成功！\n", s);
			printf("Tips: 当前剩余商品 %d 个。\n", currentCnt);
			return ;
		}
		else
		{
			puts("不合法的输入！");
			return ;
		}
	}

	while ((p -> nxt) != list_last)
	{
		if (strcmp((p -> nxt) -> info.id, s) == 0)
		{
			f = 1;
			break;
		}
		p = p -> nxt;
	}

	if (!f)
	{
		puts("您要删除的商品不存在！");
		return ;
	}

	printOneInfo((p -> nxt) -> info);
	puts("是否删除该商品？（Y/N）：");
	scanf("%s", opt);

	if (opt[0] == 'N'||opt[0] == 'n') return ;
	else if (opt[0] == 'Y'||opt[0] == 'y')
	{
		q = p;
		p = p -> nxt;
		q -> nxt = p -> nxt;
		free(p);
		currentCnt--;
		printf("Tips: 删除 ID 为 %s 的商品成功！\n", s);
		printf("Tips: 当前剩余商品 %d 个。\n", currentCnt);
	}
	else puts("不合法的输入！");
	return ;
}

void infoSearch(GoodsList *L)
{
	GoodsList *p = L;

	printf("输入需要查找的商品名称（-1 退出查找）：");
	readLine(s, 30);

	if (s[0] == '-' && s[1] == '1' && s[2] == '\0') return ;

	while (p != list_last)
	{
		if (strcmp(p -> info.name, s) == 0)
		{
			printOneInfo(p -> info);
			return ;
		}
		p = p -> nxt;
	}

	puts("您要查找的商品不存在！");
	return ;
}

void deleteAll(GoodsList **L)
{
	GoodsList *q;

	while ((*L) != NULL)
	{
		q = (*L) -> nxt;
		free(*L);
		*L = q;
	}

	*L = NULL;
	list_last = NULL;
	currentCnt = 0;
	return ;
}

void infoFlush(GoodsList *L)
{
	freopen("goodsinfo.txt", "w", stdout);
	GoodsList *p = L;

	while (p != list_last)
	{
		#define a p->info
		printf("%s\t%s\t%d\t%s\t%d\t%d\n", a.id, a.name, a.price, a.discount, a.amount, a.remain);
		#undef a

		p = p -> nxt;
	}

	fclose(stdout);
	return ;
}

void bubbleSort(GoodsList **L)
{
	int i, j;

	if (currentCnt <= 1) return ;

	for (i = 0; i < currentCnt; i++)
	{
		GoodsList *p = *L, *q = (*L) -> nxt, *r;

		if (p -> info.price > q -> info.price)
		{
			p -> nxt = q -> nxt;
			q -> nxt = p;
			*L = q;
		}

		p = *L;

		for (j = 1; j < currentCnt - i - 1; j++)
		{
			q = p -> nxt;
			r = q -> nxt;

			if (q -> info.price > r -> info.price)
			{
				q -> nxt = r -> nxt;
				r -> nxt = q;
				p -> nxt = r;
			}

			p = p -> nxt;
		}
	}
	return ;
}

int main()
{
	readAndInitialize(&list, &list_last);
	puts("超市商品管理系统");
	while (1)
	{
		char opt[3];

		outputMenu();
		printf("输入您的选择：");
		scanf("%s", opt);

		switch (opt[0])
		{
			case  '1': printAllInfo(list);break;
			case  '2': infoChange(&list);break;
			case  '3': infoInsert(&list, &list_last);break;
			case  '4': infoDelete(&list);break;
			case  '5': infoSearch(list);break;
			case  '6': infoFlush(list);deleteAll(&list);return 0;
			case  '7': bubbleSort(&list);break;
			case  '8': deleteAll(&list);break;
			default: return 0;
		}

		puts("");
	}
	return 0;
}
