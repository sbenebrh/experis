#include<stdlib.h>
#include"deck.h"
#include"players.h"
#include"game.h"
#include"round.h"

#define NCARDS 52
struct Game
{
	Deck* m_deck;
	Player* *m_players;
	int m_endGame;
	Round* m_round;
	
};

/*#############STATIC##################################*/
static void initScore(Game* _game);
static void getMinScore(Game* _game,int* _winner,int* minScore, int* _scores);
/*####################################################*/

Game* GameCreate(Player* *_players, int _endGame)
{
	int flagErr = 0, i;
	Game* newGame;

	for(i = 0;i < NPLAYERS ; ++i)
	{
		if(!_players)
		{
			return NULL;
		}
	}

	newGame = (Game*)malloc(sizeof(Game));
	if(NULL == newGame)
	{
		return NULL;
	}

	newGame -> m_deck = CreateDeck(NCARDS);
	if(NULL == newGame -> m_deck)
	{
		free(newGame);
		return NULL;
	}
	newGame -> m_players = _players;
	
	newGame -> m_round = CreateRound();
	if(NULL == newGame -> m_round)
	{
		DestroyDeck(newGame -> m_deck);
		free(newGame);
		return NULL;
	}

	return newGame;

}


void DestroyGame(Game* _game)
{
	if(NULL != _game)
	{
		DestroyDeck(_game -> m_deck);
		DestroyRound(_game -> m_round);
		free(_game);
	}
}

void flowGame(Game* _game)
{
	char name[16];
	PASS mode = 0;
	int scores[NPLAYERS] = {0};	 
	int roundScore[NPLAYERS] = {0};

	int winnerScore = 0, i, minScore, winner;
	if(NULL == _game)
	{
		return;
	}

	while(winnerScore >= 0)
	{
		
		playRound(_game -> m_round, _game -> m_deck, _game ->m_players,mode, roundScore);

		UpdateScores(_game, scores,roundScore);
		for(i = 0; i < NPLAYERS; ++i)
		{
			if( scores[i] > 100)
			{
				winnerScore = scores[i];
				break;
			}
		}
		mode = (mode + 1) % 4;

	}
	getMinScore(_game, &winner, &minScore, scores);
	GetName(_game -> m_players[winner],name);
	printf("THE WINNER IS: %s with the score of %d\n", name, minScore);
}

void UpdateScores(Game* _game, int* _gameScore, int* _roundScore)
{
	int i;
	for(i = 0; i < NPLAYERS;++i)
	{
		_gameScore[i] += _roundScore[i];
	}
}






/*#######################################STATIC#####################################*/


static void getMinScore(Game* _game,int* _winner,int* _minScore, int* _scores)
{
	int min = 100, i;
	for(i = 0; i < NPLAYERS; ++i)
	{
		if(_scores[i] < min)
		{
			min = _scores[i];
			*_winner = i;
		}
	}
	*_minScore = min;
}

