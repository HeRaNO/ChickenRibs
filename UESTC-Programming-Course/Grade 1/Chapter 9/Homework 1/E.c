#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int roll_dice()
{
	return rand()%6+rand()%6+2;
}

bool play_game()
{
	int x=roll_dice(),tar;
	printf("You rolled: %d\n",x);
	if (x==7||x==11) return true;
	if (x==2||x==3||x==12) return false;
	tar=x;
	printf("Your point is %d\n",tar);
	while (1)
	{
		x=roll_dice();
		printf("You rolled: %d\n",x);
		if (x==7) return false;
		if (tar==x) break;
	}
	return true;
}

int main()
{
	int win=0,lose=0;char play;
	srand((unsigned int)time(NULL));
	while (1)
	{
		if (play_game()){puts("You win!");win++;}
		else{puts("You lose!");lose++;}
		puts("");
		printf("Play again? ");
		scanf(" %c",&play);
		if (play=='y'||play=='Y') continue;
		else break;
	}
	printf("Wins: %d  Losses: %d\n",win,lose);
	return 0;
}
