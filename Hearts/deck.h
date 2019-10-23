/**
*framework for deck
* @autor: samuel ben ibgui

* @version: 0.01
* @creation: 05/01/2019
*
* @mail: benebrhi@gmail.com
**/

#ifndef __DECK_H__
#define __DECK_H__

#include"card.h"
#include"vector/vector.h"
#include"ADTErr.h"

typedef struct Deck Deck;

/** 
 * @function: DeckCreate
 * create a pointer to a deck
 * 
 *
 * @param _numOfCards : the size of the deck
 

 * @return return pointer to the deck
 * 			if err with allocation return null
 *			
 **/
Deck* CreateDeck(size_t _numOfCards);

/** 
 * @function: DestroyDeck	
 * @brief: destroy the deck 
 * 
 * @param deck : pointer to the deck 
 *
 * @return no return value
**/
void DestroyDeck(Deck* _deck);


/** 
 * @function: ShuffleDeck	
 * @brief: shuffle the deck 
 * 
 * @param deck : pointer to the deck 
 *
 * @return no return value
**/
void ShuffleDeck(Deck* _deck);

/** 
 * @function: DeckGiveCard
 * give a card by using the id and delete from the deck
 * 
 *
 * @param _deck : pointer to the deck
 * @param _cardId : the card gave by the deck

 * @return return status of the function
 * 			if pointer = null return uninitialized
 *			
 **/
ADTErr	DeckGiveCard(Deck* _deck, int* _cardId);

/** 
 * @function: DeckTakeCard
 * take a card by using the id and add to  the deck
 * 
 *
 * @param _deck : pointer to the deck
 * @param _cardId : the card tooken by the deck

 * @return return status of the function
 * 			if pointer = null return uninitialized
 *			
 **/
ADTErr	DeckTakeCard(Deck* _deck, int _cardId);

/** 
 * @function: Deckprint	
 * @brief: print a deck 
 * 
 * @param _deck: the deck 
 * @return no return value
**/
void	Deckprint(Deck* _deck);

#endif /*__DECK_H__*/