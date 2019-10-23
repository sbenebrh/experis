#include<stdlib.h>
#include<time.h>

#include"card.h"
#include"vector/vector.h"
#include"ADTErr.h"
#include"deck.h"

#define NC 52

struct Deck
{
	Vector* m_deck;
	size_t m_NCards;
};
/*###################STATIC##########*/
static void swap(Vector* _vec, int _index1, int _index2);

/*###################################*/


Deck* CreateDeck(size_t _numOfCards)
{
	int i;
	Deck* newDeck = (Deck*) malloc(sizeof(Deck));
	if(NULL == newDeck)
	{
		return newDeck;
	}

	newDeck -> m_deck = VectorCreate(_numOfCards,0);
	if(NULL == newDeck -> m_deck)
	{
		free(newDeck);
		return NULL;
	}

	newDeck -> m_NCards = _numOfCards;
	for(i = 0; i < _numOfCards; ++i)
	{
		VectorAdd(newDeck -> m_deck, i);
	}
	return newDeck;	
}

void DestroyDeck(Deck* _deck)
{
	int i, numOfCards;

	if(_deck != NULL)
	{
		VectorDestroy(_deck -> m_deck);
		free(_deck);
	}
}


void ShuffleDeck(Deck* _deck)
{
	int index1, index2, i, ncard;
	srand(time(NULL));
	
	if(NULL == _deck)
	{
		return;
	}

	ncard = _deck -> m_NCards;
	for(i = ncard - 1; i > 1; --i)
	{
		index2 = rand()% (i) + 1;
		swap(_deck -> m_deck, i, index2);
	}

}


ADTErr	DeckGiveCard(Deck* _deck, int* _cardId)
{
	if(NULL == _deck)
	{
		return ERR_UNINITIALIZED;
	}

 	_deck -> m_NCards--;
	
	return VectorDelete(_deck -> m_deck, _cardId);
}

ADTErr	DeckTakeCard(Deck* _deck, int _cardId)
{
		if(NULL == _deck)
	{
		return ERR_UNINITIALIZED;
	}
	_deck -> m_NCards++;
	
	return VectorAdd(_deck -> m_deck, _cardId);
}


void	Deckprint(Deck* _deck)
{
	int i, numOfCards, cardId;
	if(NULL == _deck)
	{
		return;
	}

	numOfCards = _deck -> m_NCards;
	for(i = 0; i < numOfCards; i++)
	{
		VectorGet(_deck -> m_deck, i, &cardId);
		CardPrint(cardId);
	}
}

/*####################################################*/
static void swap(Vector* _vec, int _index1, int _index2)
{
	int num1, num2;
	VectorGet(_vec, _index1, &num1);
	VectorGet(_vec , _index2, &num2);

	VectorSet(_vec, _index1, num2);
	VectorSet(_vec, _index2, num1);
}