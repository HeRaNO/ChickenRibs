#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BinaryTree{
	char p;
	struct BinaryTree *lch, *rch;
}BTree;

typedef struct Seqstack{
	BTree* a;
	struct Seqstack *las;
}stack;

BTree *B1, *B2, *B3;
char str[100];
int first;
FILE * fp;
stack *sta = NULL;

BTree* top(){return sta -> a;}

int empty()
{
	if (sta == NULL) return 1;
	return 0;
}

void push(BTree* x)
{
	stack* ncon = (stack*)malloc(sizeof(stack));
	ncon -> a = x;
	ncon -> las = sta;
	sta = ncon;
	return ;
}

void pop()
{
	if (sta == NULL) return ;
	stack* tmp = sta;
	sta = sta -> las;
	free(tmp);
	return ;
}

void buildBinaryTree(BTree* now)
{
	printf("Pls input the left child of %c: ", now -> p);
	scanf("%s", str);
	if (str[0] == '#')
		now -> lch = NULL;
	else
	{
		now -> lch = (BTree*)malloc(sizeof(BTree));
		now -> lch -> p = str[0];
		buildBinaryTree(now -> lch);
	}
	printf("Pls input the right child of %c: ", now -> p);
	scanf("%s", str);
	if (str[0] == '#')
		now -> rch = NULL;
	else
	{
		now -> rch = (BTree*)malloc(sizeof(BTree));
		now -> rch -> p = str[0];
		buildBinaryTree(now -> rch);
	}
	return ;
}

void createBinaryTree()
{
	printf("Pls input the root: ");
	B1 = (BTree *)malloc(sizeof(BTree));
	scanf("%s", str);
	B1 -> p = str[0];
	buildBinaryTree(B1);
	puts("Create successfully.");
	return ;
}

void preOrder(BTree* now)
{
	if (now == NULL)
	{
		if (first)
		{
			printf("#");
			fprintf(fp, "#");
			first = 0;
		}
		else
		{
			printf(",#");
			fprintf(fp, ",#");
		}
		return ;
	}
	if (first)
	{
		printf("%c", now -> p);
		fprintf(fp, "%c", now -> p);
		first = 0;
	}
	else
	{
		printf(",%c", now -> p);
		fprintf(fp, ",%c", now -> p);
	}
	preOrder(now -> lch);
	preOrder(now -> rch);
	return ;
}

void preOrderTravelandSerialize()
{
	fp = fopen("porder.txt", "w");
	first = 1;
	printf("The preorderlize sequence is: ");
	preOrder(B1);
	fclose(fp);
	putchar('\n');
	return ;
}

int pt, n;

void buildTreeFromFile(BTree* now)
{
	if (pt >= n) return ;
	if (str[pt] == '#')
	{
		now -> lch = NULL;
		pt += 2;
	}
	else
	{
		now -> lch = (BTree*)malloc(sizeof(BTree));
		now -> lch -> p = str[pt];
		pt += 2;
		buildTreeFromFile(now -> lch);
	}
	if (str[pt] == '#')
	{
		now -> rch = NULL;
		pt += 2;
	}
	else
	{
		now -> rch = (BTree*)malloc(sizeof(BTree));
		now -> rch -> p = str[pt];
		pt += 2;
		buildTreeFromFile(now -> rch);
	}
	return ;
}

void buildTree(BTree * root)
{
	BTree * now = root;
	int f = 1;
	push(root);
	while (pt < n)
	{
		while (str[pt] != '#' && pt < n)
		{
			if (!empty())
			{
				now = top();
				if (f)
				{
					now -> lch = (BTree*)malloc(sizeof(BTree));
					now -> lch -> p = str[pt];
					now = now -> lch;
					now -> lch = NULL;
					now -> rch = NULL;
				}
				else
				{
					now -> rch = (BTree*)malloc(sizeof(BTree));
					now -> rch -> p = str[pt];
					pop();
					now = now -> rch;
					now -> lch = NULL;
					now -> rch = NULL;
					f = 1;
				}
				push(now);
			}
			pt += 2;
		}
		pt += 2;
		if (!f) pop();
		else f = 0;
	}
	return ;
}

void readandBuild(int f)
{
	fp = fopen("porder.txt", "r");
	fscanf(fp, "%s", str);
	if (!f)
	{
		B2 = (BTree*)malloc(sizeof(BTree));
		B2 -> p = str[0];
		pt = 2; n = strlen(str);
		buildTreeFromFile(B2);
		puts("Create successfully with recursive method.");
	}
	else
	{
		B3 = (BTree*)malloc(sizeof(BTree));
		B3 -> p = str[0];
		pt = 2; n = strlen(str);
		buildTree(B3);
		puts("Create successfully with non-recursive method.");
	}
	return ;
}

void inOrderTravel(BTree * now)
{
	while (!empty() || now != NULL)
	{
		while (now)
		{
			push(now);
			now = now -> lch;
		}
		if (!empty())
		{
			now = top();
			pop();
			if (first)
			{
				printf("%c", now -> p);
				first = 0;
			}
			else printf(",%c", now -> p);
			now = now -> rch;
		}
	}
	putchar('\n');
	return ;
}

void postOrderTravel(BTree * now)
{
	BTree* p;
	do {
		while (now)
		{
			push(now);
			now = now -> lch;
		}
		p = NULL;
		while (!empty())
		{
			now = top();
			if (now -> rch == p)
			{
				if (first)
				{
					printf("%c", now -> p);
					first = 0;
				}
				else printf(",%c", now -> p);
				p = now;
				pop();
			}
			else
			{
				now = now -> rch;
				break;
			}
		}
	} while (!empty());
	putchar('\n');
	return ;
}

void destructTree(BTree* now)
{
	if (now == NULL) return ;
	destructTree(now -> lch);
	destructTree(now -> rch);
	free(now);
	return ;
}

void printTree(BTree *now)
{
	if (now == NULL) return ;
	printf("%c", now -> p);
	printTree(now -> lch);
	printTree(now -> rch);
	return ;
}

int main()
{
	createBinaryTree();
	preOrderTravelandSerialize();

	readandBuild(0);
	readandBuild(1);

#ifdef DEBUG
	printTree(B2);putchar('\n');
	printTree(B3);putchar('\n');
#endif

	first = 1;
	printf("The inorder travel sequence is: ");
	inOrderTravel(B2);

	first = 1;
	printf("The postorder travel sequence is: ");
	postOrderTravel(B3);

	destructTree(B1);
	puts("Destruct successfully.");

	destructTree(B2);
	puts("Destruct successfully.");

	destructTree(B3);
	puts("Destruct successfully.");

	puts("\nAll methods run successfully.");
	return 0;
}
