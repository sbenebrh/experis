/*
 * struct_funcs.h
 * function for data structure
 * Version: 1.0
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
 */


#include<stdio.h>
#define SEGMENTATION_FAULT -3
#define NOT_IN_THE_ARRAY -2
#define ERR_INPUT -1
#define ERR_UNDERFLOW -4
#define ERR_INCREASE -5
#include<stdlib.h>
/** 
 * create a new dynamic array with _size element 
 * if the allocation doesn`t work return SEGMENTATION_FAULT
 *
 * @param _size : the size of the array 
 * @param _numOfElement : change the number element in the array to 0

 * @return return pointer to the begining of the empty array
 * @Errors: if size less than 0 return NULL
 * 			SEGMENTATION_FAULT if memory allocation was detect
 **/
int * Dcreate(int _size, int * _numOfElement);

 /** 
 * destroy the dynamic array if it exit
 * 
 * @param _ptr : pointer to the begining of the array
 *
 * @return no return value
 **/
void Ddestroy(int * _ptr);

/**
* add the data element at the end of the array
* if the allocation is full increase allocation
*
* @param ** _arr : pointer of pointer to the begining of the allocating space
* @param _data : the data to add to the end of the array
* @param *_size : pointer to the size of the array change in case of the allocation is full
* @param *_numOfElement : pointer to the number of element in the array to add 1
* @param _increaseBlock : number of block to add if not enough slot
*
* @return the status of add 
*
* @errors : overflow
*			error input
*			realloc fail
*			segmentation fault
**/ 
int Dadd(int ** _arr, int _data, int * _size, int * _numOfElement, int _increaseBlock);

/**
* remove the data element from  the array
*
* @param * _arr : pointer to the begining of the allocating space
* @param _data : the data to remove 
* @param *_size : size of the array 
* @param *_numOfElement : pointer to the number of element in the array to remove 1
*
* @return the removed data if data not in the array return NOT_IN_THE_ARRAY
*
* @errors : underflow
*			error input
*			segmentation fault
*			
**/
int Dremove(int * _arr, int * _data, int _size, int * _numOfElement);

/** 
 * print the element of the array
 * 
 * @param _arr : pointer to the begining of the array
 * @param __numOfElement :  the number element in the array 
 *
 * @return no return value
 * @errors: segmentation fault
 *			error input
 **/
void print(int * _arr, int  _numOfElement);

