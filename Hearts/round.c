#include<stdlib.h>

#include"players.h"
#include"card.h"
#include"deck.h"

#include"game.h"
#include"round.h"
#include"trick.h"
#include"vector/vector.h"


struct Round
{
	Trick* m_trick;
};
/*################STATIC##############################*/
static void DealCard(Deck* _deck, Player** _players);
static void PrintHands(Player** _players);
static void PassCard(Player** _players,PASS _passCards);
static int ChooseStarter(Player** _players);
static void printNtricks(int _trickNumbers);
static void initDeck(Deck* _deck);
static void printScore(int* _scores);
/*###################################################*/
Round* CreateRound()
{
	Round* newRound = (Round*)malloc(sizeof(Round));
	if(NULL == newRound)
	{
		return NULL;
	}

	newRound -> m_trick = TrickCreate();
	if(NULL == newRound -> m_trick)
	{
		free(newRound);
		return NULL;
	}
	

	return newRound;
}


void DestroyRound(Round* _round)
{
	if(NULL == _round)
	{
		return;
	}
	TrickDestroy(_round -> m_trick);
	free(_round);
}

void playRound(Round* _round, Deck* _deck,Player* *_players,PASS _mode, int *_scores)
{
	int i;
	int leader, winner, score;
	ShuffleDeck(_deck);

	DealCard(_deck , _players);

	PrintHands(_players);

	PassCard(_players, _mode);

	PrintHands(_players);

	 leader = ChooseStarter(_players);

	printNtricks(0); 
	TrickPlay(_round -> m_trick,_players,leader,&winner,&score, 1);
	leader = winner;
	_scores[leader] += score;
	printScore(_scores);

	for(i = 1; i < NTRICKS ; ++i)
	{
		printNtricks(i);
		TrickPlay(_round -> m_trick,_players,leader,&winner,&score, 0);
		leader = winner;
		_scores[leader] += score;
		printScore(_scores);
			
	}

	initDeck(_deck);
	

}




/*###########################STATIC##########################*/

static void DealCard(Deck* _deck, Player** _players)
{
	int i, cardId;
	for(i = 0; i < NCARDS; ++i)
	{
		DeckGiveCard(_deck, &cardId);
		PlTakeCard(_players[i%4], cardId);
	}
}

static void PrintHands(Player* *_players)
{
	int i ;
	for(i = 0; i < NPLAYERS; ++i)
	{
		PrintHand(_players[i]);
	} 
}         

static void PassCard(Player** _players,PASS _passCards)
{
	int passPosition, i = 0, j, count = 0, maxCard = 3, cardId, returnCard,flag = 0;
	switch(_passCards)
	{
		case NONE:
			return;
		case LEFT:
			passPosition = 1;
			break;
		case RIGHT:
			passPosition = 3;
			break;
		case FRONT:
			passPosition = 2;
			break;
	}
	while(i < NPLAYERS)
	{
		/*try to give queen spades*/
		if(HasCard(_players[i],GetId(R_QUEEN, S_SPADES)))
		{
			cardId = GetId(R_QUEEN, S_SPADES);
			PlGiveCard(_players[i],&returnCard,cardId,_players[(i + passPosition)%NPLAYERS]);
			flag = 1;
		}
		if(flag)
		{
			maxCard = 2;
		}
		for(j = 0; j<maxCard;++j)
		{
			PlGiveCard(_players[i],&cardId, -1,_players[(i + passPosition)%NPLAYERS]);

		}
		maxCard = 3;
		++i;

	}

}     
  

static int ChooseStarter(Player* *_players)
{
	int i;
	int cardId = GetId(R_TWO, S_CLUBS);
	for(i = 0; i < NPLAYERS; ++i)
	{
		if(HasCard(_players[i], cardId))
		{
			return i;
		}
	}
}


static void printNtricks(int _trickNumbers)
{
	printf("\n\n***********  TRICK N. %d *************: \n\n",_trickNumbers );
}

static void initDeck(Deck* _deck)
{
	int i;
	for(i = 0; i < NCARDS; ++i)
	{
		DeckTakeCard(_deck, i);
	}
}

static void printScore(int* _scores)
{
	int i;
	printf("%s\n", "*****************THE SCORES*************");
	for(i = 0; i < NPLAYERS;++i)
	{
		printf("Player%d : %d\n",i+1,_scores[i] );
	}
	printf("%s\n", "*****************THE SCORES*************");
}
