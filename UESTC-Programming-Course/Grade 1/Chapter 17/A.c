#include <stdio.h>
#include <stdlib.h>

typedef struct node {
	int n;
	struct node* nxt;
}node;

int main()
{
	int x,r,cnt=0;
	node *pHead=(node*)malloc(sizeof(node));
	node *p=pHead;
	while (1)
	{
		p->nxt=NULL;
		scanf("%d",&x);if (!x) break;
		p->n=x;
		p->nxt=(node*)malloc(sizeof(node));
		p=p->nxt;
	}
	scanf("%d",&r);
	p=pHead;
	while (p!=NULL)
	{
		if (p->n==r) ++cnt;
		p=p->nxt;
	}
	printf("The occurrences of %d is: %d\n",r,cnt);
	return 0;
}
