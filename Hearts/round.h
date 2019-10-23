/**
* file round.h
*framework for round
* @autor: samuel ben ibgui

* @version: 0.01
* @creation: 05/01/2019
*
* @mail: benebrhi@gmail.com
**/

#ifndef __ROUND_H__
#define __ROUND_H__
#include"players.h"
#include"deck.h"


#define NTRICKS		13
typedef enum 
{
	LEFT,
	RIGHT,
	FRONT,
	NONE
}PASS;

typedef struct Round Round;


/** 
 * @function: CreateRound
 * create a pointer to a round
 * 
 *

 * @return return pointer to the round
 * 			if err with allocation return null
 *			
 **/
Round* CreateRound();

/** 
 * @function: playRound
 * play a new round
 * 
 * @param _round: pointer to the round
   @param _deck: pointer to the deck
   @param _players: pointer to the array of players
 * @param _mode: the pass mode to give card to other players
 * @param _ scores: pointer to the array of scores

 * @return no return value
 *			
 **/
void playRound(Round* _round, Deck* _deck,Player* *_players,PASS _mode, int *_scores);

/** 
 * @function: DestroyRound	
 * @brief: destroy the round 
 * 
 * @param _round : pointer to the round
 *
 * @return no return value
**/
void DestroyRound(Round* _round);

#endif