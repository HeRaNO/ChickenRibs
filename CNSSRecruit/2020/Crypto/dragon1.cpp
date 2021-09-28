#include <cstdio>
#define MAXN 1000005

long long ans;
int prime[MAXN],tot;
bool not_prime[MAXN];

inline void LinearShaker(int n)
{
	for (int i=2;i<=n;i++)
	{
		if (!not_prime[i]) prime[++tot]=i;
		for (int j=1;i*prime[j]<=n;j++)
		{
			not_prime[i*prime[j]]=true;
			if (!(i%prime[j])) break;
		}
	}
	return ;
}

int main(int argc, char const *argv[])
{
	LinearShaker(999999);
	for (int i=1;i<=tot;i++) ans+=1LL*prime[i]*prime[i];
	printf("%lld\n",ans);
	return 0;
}