#include<stdio.h>
#include<stdlib.h>
#include"card.h"


#define SPADE   "\xE2\x99\xA0"
#define CLUB    "\xE2\x99\xA3"
#define HEART   "\xE2\x99\xA5"
#define DIAMOND "\xE2\x99\xA6"
struct  Card
{
	Rank m_rank;
	Suite m_suite;
};

static Card* s_catalog[NCARDS];
/*#################STATIC FUNCTIONS##############*/
static void PrintUpperRank(int _cardid, char suite[16]);
/*###############################################*/

Card* CardCreate(Rank _rank, Suite _suite)
{
	Card* newCard = (Card*) malloc(sizeof(Card));
	if(NULL == newCard)
	{
		return newCard;
	}

	newCard -> m_suite = _suite;
	newCard -> m_rank = _rank;

	return newCard;
}

void CardDestroy(Card* _card)
{
	int i;
	if(NULL == _card)
	{
		return;
	}
	for(i = 0;i < NCARDS; ++i)
	{
		free(s_catalog[i]);
	}
	

}

void initCatalog()
{
	int i;
	for (i = 0; i < NCARDS; ++i)
	{
		Card* card = CardCreate(RANK(i),SUITE(i));
		s_catalog[i] = card;
	}
}

Suite GetSuite(int _cardId)
{
	return s_catalog[_cardId] -> m_suite;
}

Rank GetRank(int _cardId)
{
	return s_catalog[_cardId] -> m_rank;
}

int GetId(Rank _rank, Suite _suite)
{
	return _rank - 2 + _suite * 13;
}

void GetCard(int _cardId, Card* _card)
{
	if(NULL == _card)
	{
		return;
	}
	*_card = *s_catalog[_cardId];
	
}

void CardPrint(int _cardid)
{

	switch(s_catalog[_cardid] -> m_suite)
	{
		case S_CLUBS:
			if(s_catalog[_cardid] -> m_rank > 10)
			{
				PrintUpperRank(_cardid, CLUB );
				break;
			}
			printf("%s %d\t",CLUB, s_catalog[_cardid]-> m_rank );
			break;
		case S_SPADES:
			if(s_catalog[_cardid] -> m_rank > 10)
			{
				PrintUpperRank(_cardid, SPADE);
				break;
			}
			printf("%s %d\t",SPADE, s_catalog[_cardid] -> m_rank );
			break;
		case S_HEARTS:
			if(s_catalog[_cardid] -> m_rank > 10)
			{
				PrintUpperRank(_cardid, HEART );
				break;
			}
			printf("%s %d\t",HEART, s_catalog[_cardid]-> m_rank );
			break;
		case S_DIAMONDS:
			if(s_catalog[_cardid] -> m_rank > 10)
			{
				PrintUpperRank(_cardid, DIAMOND );
				break;
			}
			printf("%s %d\t",DIAMOND, s_catalog[_cardid] -> m_rank );
			break;
	}
}

static void PrintUpperRank(int _cardid, char suite[16])
{
	char rank;
	switch(s_catalog[_cardid] -> m_rank)
	{
		case 11:
			rank = 'J';
			break;

		case 12:
			rank = 'Q';
			break;

		case 13:
			rank = 'K';
			break;

		case 14:
			rank = 'A';
			break;
	}
	printf("%s %c\t", suite, rank);
}