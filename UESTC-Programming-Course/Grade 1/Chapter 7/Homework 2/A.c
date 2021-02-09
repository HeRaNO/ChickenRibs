#include <stdio.h>

int main()
{
	char c;int a=0;
	puts("Enter a word: ");
	while (1)
	{
		c=getchar();
		if (c<32) break;
		if (c>='A'&&c<='Z') c+=32;
		if (c=='d'||c=='g') a+=2;
		else if (c=='b'||c=='c'||c=='m'||c=='p') a+=3;
		else if (c=='f'||c=='h'||c=='v'||c=='w'||c=='y') a+=4;
		else if (c=='k') a+=5;
		else if (c=='j'||c=='x') a+=8;
		else if (c=='q'||c=='z') a+=10;
		else ++a;
	}
	printf("Scrabble value: %d\n",a);
	return 0;
}
