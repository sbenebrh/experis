/*
 * struct_funcs.h
 * framework for daily calendar
 * Version: 1.0
 * creation: 06/12/2018
 * last change: 08/12/2018
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
 */

#include<stdio.h>

enum status {ERR_INPUT = -3,
	SEGMENTATION_FAULT = -1,
	NOT_ENOUGH_SPACE,
	ERR_OVERLOADING_MEETING,
	ERR_REALLOCATION,
	UNKNOWN_MEETING = -2,
	IS_SWAPPED = 0,
	WELL};



typedef struct  AD AD;


typedef struct 
{
	float begin;
	float end;
	int room;
} meeting_t;
/** 
 * @function: ADCreate
 * create a pointer to a struct witch his contains a new dynamic array of pointer to meeting
 * and every needed information about the array 
 *
 * @param _size : the size of the array of pointers
 * @param _incrementBlockSize : the number of blocks which the user want to add in case of not enough place in the array

 * @return return pointer to the struct

 * @errors: if size less than 0 or _incrementBlockSize return ERR_INPUT
 *			if size AND _incrementBlockSize equals to 0 return return ERR_INPUT
 *			if the pointer to the struct was not create propely or the pointer to the array return SEGMENTATION_FAULT
 **/
AD * ADCreate(int _size, int _incrementBlocks);/* done*/
meeting_t * createMeeting(float _begin, float _end, int _room);/*done*/
enum status InsertMeeting(AD * _DAptr, meeting_t * _meeting);/*done*/
enum status RemoveMeeting(AD * _DAptr, meeting_t* * _removedMeeting, float _begining);/*done*/
int FindMeeting(const AD * const _DAptr, float _begining, meeting_t* *_findedMeeting );/*done*/

/** 
 * @function: Ddestroy	
 * destroy every meeting in the dynamic array and even the array itself and the pointer to the struct
 * 
 * @param _Daptr : pointer to the struct
 *
 * @return no return value
 **/
void ADDestroy(AD * _DAptr);/*done*/

/** 
 * @function: ADprint
 * print every element of the array wich it is in the struct
 * 
 * @param _Daptr : pointer to the struct
 *
 * @return status of printing
 * @error: segmentation fault
 **/
enum status ADPrint(const AD * const _DAptr);/*done*/

