#include <cstdio>
#include <vector>
#include <algorithm>

#define MAXN 100000
#define MAXR 50
#define MAXL 19

vecotr <int> G[MAXN];

//以下记 n 为系统中用户数，m 为用户平均好友量

void readListandTrim()
{
	//读取列表信息，并将 ID 离散化，作为这个人的编号
	//时间复杂度 O(nm log nm) 
}

void makeGraph()
{
	//按照 readListandTrim() 函数生成的信息重新建图，用邻接表或 vector 存储图，需要按终点编号从小到大的顺序插入边信息。
	//时间复杂度 O(nm log m)
}

bool query(long long x, long long y)
{
	//方法一：
	//先获得 x, y 两人的哈希值，然后遍历 x 的每个后继节点，二分查找它们的后继是否存在 y 即可。
	//单次查询时间复杂度 O(m log m)，空间复杂度 O(nm)
	for (int i = 0; i < G[x].size(); i++)
	{
		int v = G[x][i];
		int p = lower_bound(G[v].begin(), G[v].end(), y);
		if (G[v][p] == y) return true;
	}
	return false;

	//方法二：
	//对于二分查找，再次用哈希替代，将查询第二层的复杂度降为 O(1)
	//单次查询时间复杂度 O(m)，空间复杂度 O(np)，其中 p 为用于哈希的质数。
}

int main()
{
	readListandTrim();
	makeGraph();

	int queryNumber;
	scanf("%d", &queryNumber);

	while (queryNumber--)
	{
		long long x, y;
		scanf("%lld %lld", &x, &y);
		if (query(ori[x], ori[y])) puts("Yes");
		else puts("No");
	}
	return 0;
}