/**
*framework for games
* @autor: samuel ben ibgui

* @version: 0.01
* @creation: 05/01/2019
*
* @mail: benebrhi@gmail.com
**/

#ifndef __TRICK_H__
#define __TRICK_H__
#include "players.h"
#include"card.h"

#define NPLAYERS	4

typedef struct Trick Trick;

/**
* @function : TrickCreate
* @brief  : Create a Trick

* @return : A pointer to the Trick is returned
		 if there is an allocation fail return null
*/
Trick*	TrickCreate();

/**
* @function : TrickDestroy
* @brief  : Destroy a trick
* @params _trick: A pointer to the trick to destroy
* @return : no return value
*/
void	TrickDestroy(Trick* _trick);


/**
* @brief  : Play a trick by : take a card from each player, and find the winner
* @params _trick: A pointer to the trick to play
* @params _players:	pointer to the array of players
* @params _leader: The index of the trick leader
* @params _winner: pointer to the winner index
* @return : no return value
*/	
void	TrickPlay(Trick* _trick, Player** _players, int  _leader, int* _winner, int* _Score, int _flag);



#endif