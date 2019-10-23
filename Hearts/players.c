/*
* players.c
* miss algorithm for forbid user to play hearts or Queen spade at the first trick(have to had flag heart brocken and from the trick send it)
*
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#include"vector/vector.h"
#include"card.h"
#include"players.h"

#define HAND_SIZE 13
#define SUITE 4
struct Player
{
	Vector* m_hand[SUITE];
	char m_name[16];
	int m_IsAi;
};

/*##############STATIC##########################*/
static void swap(Vector* _vec, int _index1, int _index2);
static int CanPlayHearts(Player* _player, Suite _suite);
static void Userplaycard(Player* _player,Suite* _suite);
static void transformUserCard(char _card,int _rank ,int* cardId, Suite* _s);
static int findIndex(Player* _player,int cardId);
static void UserGiveCard(Player* _player,int* _cardId,Player* _receiver);
/*##############################################*/

Player* PlayerCreate(char* _name, int _isIA)
{
	int lenght, i, flagError = 0;
	Player* newPlayer; 
	if(NULL == _name)
	{
		return NULL;
	}
	/*allocation for player*/
	newPlayer = (Player*)malloc(sizeof(Player));
	if(NULL == newPlayer)
	{
		return NULL;
	}



	strcpy(newPlayer -> m_name, _name);

	/* allocation for pointer of vector(the hand of the player)*/
	for(i = 0; i < SUITE; ++i)
	{
		newPlayer -> m_hand[i] = VectorCreate(HAND_SIZE, 0);
		if(NULL == newPlayer -> m_hand[i])
		{
			flagError = 1;
		}

	}
	/*if error in allocation of hand*/
	if(1 == flagError)
	{
		for(i = 0 ; i < SUITE; ++i)
		{
			VectorDestroy(newPlayer -> m_hand[i]);
		}
		free(newPlayer);
		return NULL;
	}

	newPlayer -> m_IsAi = _isIA;

	return newPlayer;


}

void 	PlayerDestroy(Player* _player)
{
	int i;

	if (NULL == _player)
	{
		return;
	}

	for(i = 0; i < SUITE; ++i)
	{
		VectorDestroy(_player -> m_hand[i]);
	}
	free(_player);
}


void 	PlayCard(Player* _player, Suite _suite, int* _cardId)
{
	int size, i;
	Suite playSuite;
	if( _player -> m_IsAi != 0)
	{
		if(NULL == _player || NULL == _cardId)
		{
			return;
		}
		/*play the appropriate suite*/
		if(HasSuite(_player,_suite))
		{
			playSuite = _suite;

		}
		/*playHearts*/
		VectorItemsNum(_player ->m_hand[S_HEARTS],&size);
		if (CanPlayHearts(_player, _suite) && size)
		{
			playSuite = S_HEARTS;
		}
		else
		{
			for(i = 0; i < 4; ++i)
			{
				if(i != _suite && i != S_HEARTS)
				{
					size = 0;
					VectorItemsNum(_player->m_hand[i], &size);
					{
						if(size  > 0)
						{
							playSuite = i;
							break;
						}
					}
				}
			}

			VectorItemsNum(_player ->m_hand[playSuite], &size);
			swap(_player ->m_hand[playSuite], 0, size -1);
		}
	}else
	{
		
		Userplaycard(_player, &_suite);
		playSuite = _suite;
	}

		VectorDelete(_player -> m_hand[playSuite], _cardId);
}

ADTErr	PlTakeCard(Player* _player, int _cardId)
{
	int size;
	Suite s;
	
	if(NULL == _player)
	{
		return ERR_UNINITIALIZED;
	}
	
	s = GetSuite(_cardId);
	
	/*always have the two clubs at the begining of the vector*/
	if(s == S_CLUBS && GetRank(_cardId) == R_TWO)
	{
		VectorAdd(_player -> m_hand[s], _cardId);
		VectorItemsNum(_player -> m_hand[s], &size);
		swap(_player -> m_hand[s], 0,size - 1);
		return ERR_OK;
	}

	return VectorAdd(_player -> m_hand[s], _cardId);


}


int		HasCard(Player* _player, int _cardId)
{
	
	Suite cardSuite;
	int size, i, cardId;

	if(NULL == _player)
	{
		return 0;
	}

	
	cardSuite = GetSuite(_cardId);
	

	VectorItemsNum(_player -> m_hand[cardSuite], &size);
	if(size)
	{
		for(i = 0; i < size; ++i)
		{
			VectorGet(_player -> m_hand[cardSuite], i, &cardId);
			if(cardId == _cardId)
			{
				return 1;
			}
		}
	}
	return 0;
}

void 	PrintHand(Player* _player)
{
	int i, size, j, cardId;
	char name[16];
	

	if(NULL == _player)
	{
		return;
	}
	strcpy(name, _player -> m_name);
	printf("Player : %s\n",name);

	for(i = 0; i < SUITE; ++i)
	{
		VectorItemsNum(_player -> m_hand[i], &size);
		for(j = 0; j < size; ++j)
		{
			VectorGet(_player -> m_hand[i], j , &cardId);
			CardPrint(cardId);

		}
		printf("\n");
	}

}



void	GetName(Player* _player, char* _name)
{
	if(NULL == _player || NULL == _name )
	{
		return;
	}
	strcpy( _name,_player -> m_name); 
}




ADTErr	PlGiveCard(Player* _player, int* _cardId, int _flag, Player* _receiver)
{
	int lastCardid = -1, temp, i, tempcard;

	if(NULL == _player || NULL == _cardId )
	{
		return ERR_UNINITIALIZED;
	}
	if( _player -> m_IsAi != 0)
	{
		/*give the last card*/
		temp = SUITE - 1;
		while(lastCardid == -1)
		{
			--temp;
			VectorItemsNum(_player -> m_hand[temp],&lastCardid);
			
		}
		/*if we want to give the queen spade*/
		if(_flag)
		{
			VectorItemsNum(_player -> m_hand[S_SPADES],&lastCardid);
			for(i = 0; i < lastCardid; ++i )
			{
				VectorGet(_player -> m_hand[S_SPADES],i,&tempcard);
				if(GetRank(tempcard) == R_QUEEN)
				{
					swap(_player -> m_hand[S_SPADES], i, lastCardid -1);
					temp = S_SPADES;
					break;
				}
			}
		}
		
		VectorDelete(_player -> m_hand[temp], &lastCardid);
		*_cardId = lastCardid;
		/*give to the player*/
	
	return VectorAdd(_receiver -> m_hand[temp], lastCardid );
	}
	else
	{
		UserGiveCard(_player, _cardId, _receiver);
		return ERR_OK;
	}
	
}



int HasSuite(Player* _player,Suite _suite)
{
	int size;
	VectorItemsNum(_player -> m_hand[_suite], &size);
	if(size)
	{
		return size;
	}
	return 0;
}



ADTErr	PlPlayTwoClub(Player* _player)
{
	int size;
	char c;
	int rank, cardId = -1;
	Suite s;

	if(_player -> m_IsAi)
	{
		if(NULL == _player)
		{
			return ERR_UNINITIALIZED;
		}
		VectorItemsNum(_player -> m_hand[S_CLUBS], &size);
		if(0 == size)
		{
			return ERR_EMPTY;
		}
	}
	else
	{
		while(cardId != 0)
		{
		printf("%s\n","please play 2 club" );
		scanf("%d%c",&rank, &c);
		transformUserCard(c,rank ,&cardId, &s);
		}
	}
	/*put the card to the end of the vector*/
	swap(_player -> m_hand[S_CLUBS], 0, size -1);

	return VectorDelete(_player -> m_hand[S_CLUBS], &size);
}

/*#########################################*/

static void swap(Vector* _vec, int _index1, int _index2)
{
	int num1, num2;
	VectorGet(_vec, _index1, &num1);
	VectorGet(_vec , _index2, &num2);

	VectorSet(_vec, _index1, num2);
	VectorSet(_vec, _index2, num1);
}



static int CanPlayHearts(Player* _player, Suite _suite)
{
	int size;
	if(NULL == _player)
	{
		return 0;
	}

	VectorItemsNum(_player -> m_hand[_suite], &size);
	if(!size)
	{
		return 1;
	}
		return 0;
}

static void Userplaycard(Player* _player,Suite* _suite)
{
	char card;
	Suite s;
	int rank;
	int cardId;
	int index;
	int size;

	printf("%s\n","please choose card( H/C/S/D  [2 - 14])" );
	scanf(" %c %d", &card, &rank);
	transformUserCard(card, rank , &cardId, &s);
	if(HasCard(_player, cardId))
	{
		if(s == *_suite)
		{
			index = findIndex(_player, cardId);
			VectorItemsNum(_player -> m_hand[s], &size);
			swap(_player -> m_hand[s], index, size - 1);
			return;
		}
		else if(HasSuite(_player, *_suite))
		{
			printf("%s\n","error you should play card with the same suite" );
			printf("%s\n","please choose another card" );
			Userplaycard(_player, _suite);
		}
		else
		{
			index = findIndex(_player, cardId);
			VectorItemsNum(_player -> m_hand[s], &size);
			swap(_player -> m_hand[s], index, size - 1);
			*_suite = s;
			return;
		}

	}



}


static void transformUserCard(char _card,int _rank ,int* _cardId, Suite* _s)
{
	Suite s;
	switch(_card)
	{
		case 'D':
			s = S_DIAMONDS;
			break;
		case 'C':
			s = S_CLUBS;
			break;

		case 'S':
			s = S_SPADES;
			break;
		case 'H':
			s = S_HEARTS;
			break;
	}

	*_cardId = GetId(_rank, s);
	*_s = s;
}

static int findIndex(Player* _player,int _cardId)
{
	int i, size;
	Suite s;
	int tmpcard;
	s = GetSuite(_cardId);

	VectorItemsNum(_player -> m_hand[s], &size);

	for(i = 0; i < size -1; ++i)
	{
		VectorGet(_player -> m_hand[s], i, &tmpcard);
		if(_cardId == tmpcard)
		{
			return i;
		}
	}
}

static void UserGiveCard(Player* _player,int* _cardId,Player* _receiver)
{
	char card;
	int rank; 
	Suite s;
	int index, size;
	int cardId;

	while(1)
	{
		printf("%s\n","please select card to give" );
		scanf(" %c %d", &card, &rank);
		transformUserCard(card, rank , &cardId, &s);
		if(HasCard(_player, cardId))
		{
			VectorItemsNum(_player -> m_hand[s],&size);

			index = findIndex(_player, cardId);
			swap(_player -> m_hand[s], index, size - 1);

			VectorDelete(_player -> m_hand[s], &cardId);
			*_cardId = cardId;

			VectorAdd(_receiver -> m_hand[s], cardId);

			break;

		}
	}

}