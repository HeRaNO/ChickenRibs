#include <stdio.h>
#include <string.h>
#define MAXN 1000010

char s[MAXN],sta[MAXN];
int n,i,top,f;

int main()
{
	puts("Enter parentheses and/or braces:");
	scanf("%s",s);n=strlen(s);
	for (i=0;i<n&&!f;i++)
	{
		if (s[i]=='('||s[i]=='{') sta[++top]=s[i];
		else
		{
			if (top)
			{
				if (s[i]=='}'&&sta[top]=='{') --top;
				if (s[i]==')'&&sta[top]=='(') --top;
			}
			else f=1;
		}
	}
	if (top||f) puts("Parentheses/braces are not nested properly");
	else puts("Parentheses/braces are nested properly");
	return 0;
}
