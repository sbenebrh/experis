
/*
 * struct_funcs.h
 * framework for vector
 * Version: 1.0
 * creation: 10/12/2018
 * last change: 11/12/2018
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
*/

#ifndef _VECTOR_H
#define _VECTOR_H
#include<stdio.h>
#include"ADTErr.h"
typedef struct Vector Vector;


struct Vector
{
	int m_originalSize;
	int * m_items;
	size_t m_size;
	size_t m_nitems;
	size_t m_blockSize;
};


/** 
 * @function: VectorCreate
 * create a pointer to a struct witch his contains a new dynamic array of int
 * and every needed information about the array 
 *
 * @param _size : the size of the array 
 * @param _incrementBlockSize : the number of blocks which the user want to add in case of not enough place in the array
 * @return return pointer to the struct
 * @errors: if size AND _incrementBlockSize equals to 0 return return ERR_INPUT
 *			if the pointer to the struct was not create propely or the pointer to the array return SEGMENTATION_FAULT
 **/
Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize);

/** 
 * @function: VectorCreate	
 * destroy the array and the struct
 * 
 * @param _Daptr : pointer to the struct
 *
 * @return no return value
**/
void VectorDestroy(Vector* _vector);

/**
* @function: VectorAdd
* add the data element at the end of the array
* if the allocation is full increase allocation
*
* @param * _vector : pointer to struct
* @param _item : the data to add to the end of the array
* 
*
* @return the status of adding the data
* @errors: return SEGMENTATION_FAULT if their is no allocation for the struct or for the array
*          return NOT_ENOUGH_BLOCKS if their is no more place in the array and we cant increase it
*		   return the oldest array if we have a problem with realloc 
**/
ADTErr VectorAdd(Vector* _vector, int _item);

/**
* @function: VectorDelete 
* remove the last element of the array
* if free is bigger than 1 realloc to 1
*
* @param * _Daptr : pointer to the struct
* @param _item : the removed data
*
* @return the status of the operation
* @errors: return SEGMENTATION_FAULT if their is no allocation for the struct or for the array
* 		   return EMPTY_ARRAY if the array is empty	
*		   return not in the array if the item not in the array		 	
**/
ADTErr VectorDelete(Vector* _vector, int* _item);

/**
* @function: VectorGet 
* get the item at the index position
* 
*
* @param * _vector : pointer to the struct
* @param _item : the data at the inddex position
* @param _index : index in the array wich i want to get
* @return the status of the operation
* @errors: return SEGMENTATION_FAULT if their is no allocation for the struct or for the array
* 		   return EMPTY_ARRAY if the array is empty	
*          	 	
**/
ADTErr VectorGet(Vector* _vector, size_t _index, int * item);

/**
* @function: VectorSet 
* change the value at a specific index
* 
*
* @param * _vector : pointer to the struct
* @param _item : the data at the inddex position
* @param _index : index in the array wich i want to set

* @return the status of the operation

* @errors: return SEGMENTATION_FAULT if their is no allocation for the struct or for the array
* 		   return EMPTY_ARRAY if the array is empty	
*          return OVERFLOW if the index is bigger than the number of element in the array	 	
**/
ADTErr VectorSet(Vector* _vector, size_t _index, int  item);

/**
* @function: VectorItemsNum 
* get the number of element in the array
* 
*
* @param * _vector : pointer to the struct
* @param _numOfItems : pointer to the number of items

* @return the status of the operation

* @errors: return SEGMENTATION_FAULT if their is no allocation for the struct or for the array
* 		   return EMPTY_ARRAY if the array is empty	
*          	 	
**/
ADTErr VectorItemsNum(Vector* _vector, int* _numOfItems);

/** 
 * @function: VectorPrint
 * print every element of the array wich it is in the struct
 * 
 * @param _Daptr : pointer to the struct
 *
 * @return status of printing
 * @error: segmentation fault
 **/
void VectorPrint(Vector* _vector);


void initializeVector(Vector* _vector,size_t  _initialSize,size_t _extensionBblockSize);



#endif/*_VECTOR_H*/