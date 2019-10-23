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
	Player* players[NPLAYERS];
	Deck* m_deck = CreateDeck(52);
	ShuffleDeck(m_deck);
	players[0] = PlayerCreate("sam", 1);
	players[1] = PlayerCreate("jon", 1);
	players[2] = PlayerCreate("aaa", 1);
	players[3] = PlayerCreate("dvd", 1);

	initCatalog();
	Game* game = GameCreate(players, 100);

	flowGame(game);

	DestroyGame(game);

	for(i = 0; i < NPLAYERS;++i)
	{
		PlayerDestroy(players[i]);
	}

	return 0;
}

