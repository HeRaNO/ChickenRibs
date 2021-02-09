#include <stdio.h>
#include <stdbool.h>

int capitalization(char str[])
{
	bool f=true;int cnt=0,i;
	for (i=0;str[i]!='\0';i++)
	{
		if (f)
		{
			if (str[i]>='a'&&str[i]<='z') ++cnt,str[i]-=32;
			f=false;
		}
		if (str[i]==' ') f=true;
	}
	return cnt;
}

int main()
{
	char s[1000];int n;
	puts("Pls input a sentence: ");
	fgets(s,1000,stdin);
	n=capitalization(s);
	printf("Total words: %d\n",n);
	printf("After capitalization: %s",s);
	return 0;
}
