#include <bitset>
#include <vector>
#include <cstdio>

bool isprime(int x)
{
	for (int i=2;i*i<=x;i++)
		if (!(x%i)) return false;
	return true;
}

//A naive algorithm, Time complexity: O(n\sqrt n) Space comlexity: O(n)
std::vector <int> prime1(int n)
{
	std::vector <int> v;
	for (int i=2;i<=10;i++)
		if (isprime(i)) v.push_back(i);
	return v;
}

//Sieve of Eratosthenes, Time complexity: O(n loglog n) Space comlexity: O(n)
std::vector <int> prime2(int n)
{
	std::vector <int> v;
	std::bitset <101> not_prime(0);
	for (int i=2;i<=n;i++)
		if (!not_prime[i])
		{
			v.push_back(i);
			for (int j=i+i;j<=n;j+=i) not_prime[j]=1;
		}
	return v;
}

//Linear shaker, Time complexity: O(n) Space comlexity: O(n)
std::vector <int> prime3(int n)
{
	std::vector <int> v;
	std::bitset <10001> not_prime(0);
	for (int i=2;i<=n;i++)
	{
		if (!not_prime[i]) v.push_back(i);
		for (int j=0;i*v[j]<=n&&j<v.size();j++)
		{
			not_prime[i*v[j]]=1;
			if (!(i%v[j])) break;
		}
	}
	return v;
}

int main()
{
	std::vector <int> v=prime3(10000);
	for (int i=0;i<v.size();i++) printf("%d\n",v[i]);
	//prime2(100);
	//prime3(10000);
	return 0;
}