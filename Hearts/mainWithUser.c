#include<stdio.h>
#include"card.h"
#include"deck.h"
#include"players.h"
#include"game.h"
#include"round.h"
#include"vector/vector.h"

#define NCARDS 52
#define NPLAYERS	4
#define END		100
int main()
{
	int card,i;
	char name[16];
	int IA;
	Game* game;
	Player* players[NPLAYERS];
	Deck* m_deck = CreateDeck(52);

	printf("%s\n","please enter your name" );
	scanf("%s",name);
	printf("%s\n","please select user or bot(0/1)" );
	scanf("%d", &IA);

	ShuffleDeck(m_deck);
	players[0] = PlayerCreate(name, IA);
	players[1] = PlayerCreate("user1", 1);
	players[2] = PlayerCreate("user2", 1);
	players[3] = PlayerCreate("user3", 1);

	initCatalog();
	game = GameCreate(players, 100);

	flowGame(game);

	DestroyGame(game);

	for(i = 0; i < NPLAYERS;++i)
	{
		PlayerDestroy(players[i]);
	}

	return 0;
}