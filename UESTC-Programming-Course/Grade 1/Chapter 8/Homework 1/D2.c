#include <stdio.h>

int main()
{
	char ch;int i;
	puts("Enter message: ");
	printf("In B1FF-speak: ");
	while (1)
	{
		ch=getchar();
		if (ch<32) break;
		if (ch>='a'&&ch<='z') ch-=32;
		switch (ch)
		{
			case 'A':ch='4';break;
			case 'B':ch='8';break;
			case 'E':ch='3';break;
			case 'I':ch='1';break;
			case 'O':ch='0';break;
			case 'S':ch='5';break;
		}
		putchar(ch);
	}
	for (i=1;i<=10;i++) putchar('!');putchar('\n');
	return 0;
}
