#include <stdio.h>
#include <string.h>

const char week[7][15]={
"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

int main()
{
	int i;char s[15];
	puts("Please enter a string:");
	scanf("%s",s);
	for (i=0;i<7;i++)
		if (strcmp(s,week[i])==0)
		{
			printf("%s is %d.\n",s,i+1);
			return 0;
		}
	puts("Not found!");
	return 0;
}