int getK_level(BTNode *b, int dep, int k)
{
	if (b == NULL) return 0;
	if (dep == k) return 1;
	return getK_level(b -> lchild, dep + 1, k) + getK_level(b -> rchild, dep + 1, k);
}

bool isSame(BTNode *a, BTNode *b)
{
	if (a == NULL && b == NULL) return true;
	if (a == NULL || b == NULL) return false;
	return isSame(a -> lchild, b -> lchild) && isSame(a -> rchild, b -> rchild);
}

void reverseTree(BTNode *a)
{
	if (a == NULL) return ;
	swap(a -> lchild, a -> rchild);
	reverseTree(a -> lchild);
	reverseTree(a -> rchild);
	return ;
}
