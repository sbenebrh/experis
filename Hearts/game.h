/**
*framework for games
* @autor: samuel ben ibgui

* @version: 0.01
* @creation: 05/01/2019
*
* @mail: benebrhi@gmail.com
**/

#ifndef __GAME_H__
#define __GAME_H__
#define NPLAYERS 4

#include"players.h"


typedef struct Game Game;

/** 
 * @function: GameCreate
 * create a pointer to the game
 * 
 *
 * @param _players : pointer to the array of players
 * @param _endGame : the end of the game
 

 * @return return pointer to the deck
 * 			if err with allocation return null
 			or if the pointer to the array is not initialized 
 *			
 **/
Game* GameCreate(Player* *_players, int _endGame);

/** 
 * @function: DestroyGame	
 * @brief: destroy the game 
 * 
 * @param _game : pointer to the game
 *
 * @return no return value
**/
void DestroyGame(Game* _game);

/** 
 * @function: flowGame	
 * @brief: the flow of the game
 * 
 * @param _game : pointer to the game
 *
 * @return no return value
**/
void flowGame(Game* _game);

/** 
 * @function: GetScore	
 * @brief: get the score of a player
 * 
 * @param _game : pointer to the game
 * @param _index: the index of the player that i want to sget his score
 * @param _score: the score that i get

 * @return no return value
**/
void GetScore(Game* _game, int _index, int* _score);

/** 
 * @function: SetGameScore	
 * @brief: set the score of a player
 * 
 * @param _game : pointer to the game
 * @param _index: the index of the player that i want to set his score
 * @param _score: the score that i set

 * @return no return value
**/
void UpdateScores(Game* _game, int* _gameScore, int* _roundScore);
#endif