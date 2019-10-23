/*
 * struct_funcs.h
 * function for data structure
 * Version: 1.0
 * creation: 06/12/2018
 * last change: 08/12/2018
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
 */
#include<stdio.h>
#include<stdlib.h>


typedef struct 
{
	int * arrData;
	int size;
	int c;
	int numOfElement;
	int incDblockSize;
}DA;
enum DAStatus{ WELL,
				SEGMENTATION_FAULT,
				ERR_INPUT,
				NOT_ENOUGH_BLOCKS,
				NOT_IN_THE_ARRAY,
				EMPTY_ARRAY
				};

/** 
 * @function: Dcreate
 * create a pointer to a struct witch his contains a new dynamic array 
 * and every needed information about the array 
 *
 * @param _size : the size of the array 
 * @param _incrementBlockSize : the number of blocks which the user want to add in case of not enough place in the array

 * @return return pointer to the struct

 * @errors: if size less than 0 or _incrementBlockSize return ERR_INPUT
 *			if size AND _incrementBlockSize equals to 0 return return ERR_INPUT
 *			if the pointer to the struct was not create propely or the pointer to the array return SEGMENTATION_FAULT
 **/

DA * Dcreate(int _size, int _incrementBlockSize);

/** 
 * @function: Ddestroy	
 * destroy the dynamic array if it exit and the struct
 * 
 * @param _Daptr : pointer to the struct
 *
 * @return no return value
 **/
void Ddestroy(DA * _Daptr);

/** 
 * @function: print
 * print every element of the array wich it is in the struct
 * 
 * @param _Daptr : pointer to the struct
 *
 * @return no return value
 **/
enum DAStatus print(DA * _Daptr);

/**
* @function: Dadd
* add the data element at the end of the array
* if the allocation is full increase allocation
*
* @param * _arr : pointer to struct
* @param _data : the data to add to the end of the array
* 
*
* @return the status of adding the data

* @errors: return SEGMENTATION_FAULT if their is no allocation for the struct or for the array
*          return NOT_ENOUGH_BLOCKS if their is no more place in the array and we cant increase it
*		   return the oldest array if we have a problem with realloc 
**/
enum DAStatus Dadd(DA * _Daptr, int _data);

/**
* @function: Dremove 
* remove the last element of the array
*
* @param * _Daptr : pointer to the struct
* @param _data : the removed data

*
* @return the status of the operation
* @errors: return SEGMENTATION_FAULT if their is no allocation for the struct or for the array
* 		   return EMPTY_ARRAY if the array is empty		 	
**/
enum DAStatus Dremove(DA * _Daptr, int * _data);

/**
* @function: Dfind
* search data in an array
*
* @param * _Daptr : pointer to the struct
* @param _data : the data to find
*
* @return the status of the operation

* @errors: return SEGMENTATION_FAULT if their is no allocation for the struct or for the array
* 		   return NOT_IN_THE_ARRAY if the data is not in the array		 	
**/
enum DAStatus Dfind(DA * _Daptr, int data);
