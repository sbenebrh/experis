/**
*framework for players
* @autor: samuel ben ibgui

* @version: 0.01
* @creation: 05/01/2019
*
* @mail: benebrhi@gmail.com
**/
#ifndef __PLAYERS_H__
#define __PLAYERS_H__

#include"ADTErr.h"
#include"card.h"

typedef struct Player Player;


/** 
 * @function: PlayerCreate
 * create a pointer to a player
 * 
 *
 * @param _name : the name of the player
 * @param _IsIa : if the player is a bot or not
 

 * @return return pointer to the player
 * 			if err with allocation return null
 *			
 **/
Player* PlayerCreate(char* _name, int _isIA);

/** 
 * @function: PlayerDestroy	
 * @brief: destroy the player 
 * 
 * @param _player : pointer to the player
 *
 * @return no return value
**/
void 	PlayerDestroy(Player* _player);

/** 
 * @function: PlayCard
 * play a card according the logic of the game and delete from the hand of the player
 * 
 *
 * @param _player : pointer to the player
 * @param _cardId : the card played by the player

 * @return return status of the function
 * 			if pointer = null return uninitialized
 *			
 **/
void 	PlayCard(Player* _player, Suite _suite, int* _cardId);

/** 
 * @function: PlGiveCard
 * give a card according the logic of the game and delete from the hand of the player to another player
 * 
 *
 * @param _player : pointer to the player who give
 * @param _cardId : the card gived by the player
 * @param _receiver : pointer to the player who receive

 * @return return status of the function
 * 			if pointer = null return uninitialized
 *			
 **/
ADTErr	PlGiveCard(Player* _player, int* _cardId, int _flag,Player* _receiver);

/** 
 * @function: PlTakeCard
 * take a card according the logic of the game and add to the hand of the player
 * 
 *
 * @param _player : pointer to the player
 * @param _cardId : the card took by the player

 * @return return status of the function
 * 			if pointer = null return uninitialized
 *			
 **/
ADTErr	PlTakeCard(Player* _player, int _cardId);

/** 
 * @function: PlPlayTwoClub
 * play 2 club 
 * 
 *
 * @param _player : pointer to the player

 * @return return status of the function
 * 			if pointer = null return uninitialized
 *			
 **/
ADTErr	PlPlayTwoClub(Player* _player);

/** 
 * @function: HasSuite
 * check if we have a specific suite 
 * 
 *
 * @param _player : pointer to the player
 * @param _suite: the suite that i check

 * @return return size of the suite 
 * 			if pointer = null return 0
 *			
 **/
int		HasSuite(Player* _player, Suite _suite);

/** 
 * @function: HasCard
 * check if we have a specific card
 * 
 *
 * @param _player : pointer to the player
 * @param _suite: the specific card
 
 * @return return status of the function
 * 			if pointer = null return uninitialized
 *			
 **/
int		HasCard(Player* _player, int _cardId);

/** 
 * @function: GetName
 * get the name of the player
 * 
 *
 * @param _player : pointer to the player
 * @param _suite: string for getting his name
 
 *			
 **/
void	GetName(Player* _player, char* _name);

/** 
 * @function: PrintHand	
 * @brief: print the hand of the player 
 * 
 * @param _player: the player i want to print
 * @return no return value
**/
void 	PrintHand(Player* _player);

#endif
