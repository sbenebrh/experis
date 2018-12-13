/*
 * struct_funcs.h
 * framework for vector
 * Version: 1.0
 * creation: 10/12/2018
 * last change: 11/12/2018
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
*/

#include"../vector/function.h"
#define MAGIC_NUMBER 0XBEEFBEEF
#define NO_MAGIC_NUMBER 0XDEADBEEF

typedef struct stack
{
	unsigned int s_magicNumber;
	Vector* vector;
}Stack;
/** 
 * @function: StackCreate
 * create a pointer to a struct witch his contains a pointer to a vector of 
 * and every needed information about the vector
 *
 * @param _size : the size of the vector 
 * @param _incrementBlockSize : the number of blocks which the user want to add in case of not enough place in the array
 * @return return pointer to the struct
 * @errors: if size AND _incrementBlockSize equals to 0 return return null
 *			if the pointer to the struct was not create propely or the pointer to the vector return ERR_ ALLOCATION
 **/
Stack* StackCreate(size_t _size, size_t _blockSize);

/** 
 * @function: StackDestroy	
 * destroy the  struct
 * 
 * @param _Daptr : pointer to the struct
 *
 * @return no return value
**/
void StackDestroy(Stack* _stack);/*done*/

/**
* @function: StackPush
* add the data element at the TO OF THE STACK
* if the allocation is full increase allocation
*
* @param * _STACK : pointer to struct
* @param _item : the data to add to the top of the stack
* 
*
* @return the status of adding the data
* @errors: return ERR_RESLLOCSTION if their is no allocation for the vector
*          return NOT_ENOUGH_BLOCKS if their is no more place in the array and we cant increase it
*		   return the oldest array if we have a problem with realloc 
**/
ADTErr StackPush(Stack* _stack, int _item);

/**
* @function: StackPop 
* remove the top of the vector
* if free space is bigger than 2 blockSize realloc to 1
*
* @param * _stack : pointer to the struct
* @param _item : the removed data
*
* @return the status of the operation
* @errors: return ERR_ALLOCATION if their is no allocation for the struct 
* 		   return EMPTY_STACK if the stack is empty	
*		  	 	
**/
ADTErr StackPop(Stack* _stack, int* _item);

/**
* @function: StackTop 
* get the item at top
* 
*
* @param * _stack : pointer to the struct
* @param _item : the data at the top
*
* @return the status of the operation
* @errors: return ERR_REALLOCATION if their is no allocation for the struct or for the array
* 		   return EMPTY_STACK if the stack is empty
*          	 	
**/

ADTErr StackTop(Stack* _stack, int* _item);

/**
* @function: StackIsEmpty 
* check if the stack is empty
* 
*
* @param * _stack : pointer to the struct
* 
*
* @return the status of the operation 1 for empty 0 for not empty
* @errors: return ERR_ALLOCATION if their is no allocation for the struct or for the array
* 		   
*          	 	
**/
int StackIsEmpty(Stack* _stack);


void StackPrint(Stack* _stack);
