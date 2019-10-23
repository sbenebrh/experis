#include<stdlib.h>
#include<stdio.h>

#include"trick.h"
#include "players.h"

struct  Trick
{
	int* m_trick;
};

/*#########STATIC DECLARATIONS###########*/
static void initTrick(Trick* _trick);
static void PlayFirstTrick(Trick* _trick,Player* *_players,int _leader);
static void PLayLeaderTrick(Trick*_trick,Player* *_players,int* _cardId,int _leader);
static int setWinner(Trick* _trick,int  _leader);
static int setScore(Trick* _trick);

/*#########################################*/
Trick*	TrickCreate()
{
	Trick* newTrick = (Trick*) malloc(sizeof(Trick));
	if(NULL == newTrick)
	{
		return newTrick;
	}

	newTrick -> m_trick = (int*) malloc(NPLAYERS * sizeof(int));
	if(NULL == newTrick -> m_trick)
	{
		free(newTrick);
		return NULL;
	}
	return newTrick;
}

void	TrickDestroy(Trick* _trick)
{
	int i;
	if(NULL == _trick)
	{
		return;
	}
	free (_trick -> m_trick);
	free(_trick);
}

void	TrickPlay(Trick* _trick, Player** _players, int  _leader, int* _winner, int* _Score, int _flag)
{
	char name[16];
	int cardId = 0, i;
	Suite s;
	int nextPlayer;
	if(NULL == _trick || NULL == _players)
	{
		return;
	}

	initTrick(_trick);
/*first trick*/
	if(_flag)
	{
		PlayFirstTrick(_trick, _players, _leader);
	}

	else
	{
		PLayLeaderTrick(_trick, _players, &cardId,_leader);
	}

	s = GetSuite(cardId);

	for(i = 1; i < NPLAYERS; ++i)
	{
		nextPlayer = (_leader + i) % NPLAYERS;
		PrintHand(_players[nextPlayer]);

		PlayCard(_players[nextPlayer], s,&cardId);
		_trick -> m_trick[nextPlayer] = cardId;

		GetName(_players[nextPlayer], name);
		printf("%s played\n",name);
		CardPrint(cardId);
		printf("\n");
		

	}

	*_winner = setWinner(_trick, _leader);

	*_Score = setScore(_trick);
}


/*######################STATICS##############################*/

static void initTrick(Trick* _trick)
{
	int i;
	for(i = 0; i < NPLAYERS; ++i)
	{
		_trick -> m_trick[i] = 0;
	}
}

static void PlayFirstTrick(Trick* _trick,Player* *_players,int _leader)
{
	char name[16];
	PrintHand(_players[_leader]);
	PlPlayTwoClub(_players[_leader]);
	_trick -> m_trick[_leader] = GetId(R_TWO, S_CLUBS);
	GetName(_players[_leader], name);
	printf("%s played\n",name);
	CardPrint(_trick -> m_trick[_leader]);
	printf("\n");


}

static void PLayLeaderTrick(Trick*_trick,Player* *_players,int* _cardId,int _leader)
{
	char name[16];
	PrintHand(_players[_leader]);
	PlayCard(_players[_leader], S_CLUBS,_cardId);
	_trick -> m_trick[_leader] = *_cardId;

	GetName(_players[_leader], name);
	printf("%s played\n",name);
	CardPrint(_trick -> m_trick[_leader]);
	printf("\n");

}

static int setWinner(Trick* _trick,int  _leader)
{
	int i, nextPlayer, winner = _leader;
	Suite s = GetSuite(_trick -> m_trick[_leader]);

	for(i = 1; i< NPLAYERS; ++i)
	{
		nextPlayer = (_leader + i) % NPLAYERS;
		if(s == GetSuite(_trick -> m_trick[nextPlayer]))
		{
			if(GetRank(_trick -> m_trick[nextPlayer] > GetRank(_trick -> m_trick[winner])))
			{
				winner = nextPlayer;
			}
		}
	}
	return nextPlayer;
}

static int setScore(Trick* _trick)
{
	int score = 0, i;

	for(i = 0; i < NPLAYERS; ++i)
	{
		if(GetSuite(_trick -> m_trick[i]) == S_SPADES  && GetRank(_trick -> m_trick[i]) == R_QUEEN)
		{
			score += 13;
		}
		if(GetSuite(_trick -> m_trick[i]) == S_HEARTS)
		{
			score += 1;
		}
	}
	return score;
}