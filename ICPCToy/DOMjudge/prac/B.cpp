#include <bits/stdc++.h>
using namespace std;

int main(int argc, char const *argv[])
{
	int T;
	scanf("%d",&T);
	while (T--)
	{
		string s;
		cin>>s;
		for (int i=0;i<s.length();i++)
			s[i]=tolower(s[i]);
		if (strstr(s.c_str(),"nan")!=NULL)
			puts("nan");
		else if (strstr(s.c_str(),"inf")!=NULL)
			puts("0");
		else
		{
			stringstream ss;
			ss<<s;
			double n;
			ss>>n;
			cout<<1.0/n<<endl;
		}
	}
	return 0;
}