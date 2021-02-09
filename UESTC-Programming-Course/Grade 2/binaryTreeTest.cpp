#include <cstdio>
#include <algorithm>
using namespace std;

#define TEST2

struct BTNode
{
	int x;
	BTNode *lchild, *rchild;
};

#include "binaryTree.cpp"

void print(BTNode *b)
{
	if (b == NULL) return ;
	if (b->lchild)printf("%d->%d\n",b->x,(b->lchild)->x);
	else printf("%d->NULL\n",b->x);
	if (b->rchild)printf("%d->%d\n",b->x,(b->rchild)->x);
	else printf("%d->NULL\n",b->x);
	print(b->lchild);print(b->rchild);
}

BTNode a[100],b[100];
int n,x,y,m,k;

int main()
{
	scanf("%d",&n);
	if (n) a[0].lchild=&a[1];
	for (int i=1;i<=n;i++)
	{
		scanf("%d %d",&x,&y);
		if (x) a[i].lchild=&a[x];
		if (y) a[i].rchild=&a[y];
	}

	#ifdef TEST1
		//1. Output the number of the nodes at level k in a binary tree.
		scanf("%d",&k);
		printf("%d\n",getK_level(&a[0],0,k));
	#endif

	#ifdef TEST2
		//2. Determine whether two binary trees are isomorphic.
		scanf("%d",&m);
		if (m) b[0].lchild=&b[1];
		for (int i=1;i<=m;i++)
		{
			scanf("%d %d",&x,&y);
			if (x) b[i].lchild=&b[x];
			if (y) b[i].rchild=&b[y];
		}
		if (isSame(&a[0],&b[0])) puts("Yes");
		else puts("No");
	#endif

	#ifdef TEST3
		//3. Reverse a binary tree
		for (int i=1;i<=n;i++) a[i].x=i;
		reverseTree(&a[1]);
		print(&a[1]);
	#endif

	return 0;
}
