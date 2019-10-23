#ifndef __HEAP_H__
#define __HEAP_H__
#include"ADTErr.h"
#include"vector.h"


typedef struct Heap Heap;



/**
* @function: HeapBuild
* @brief create a heap from a vector
* 
* @param _vec: a pointer to the vector that i want change to heap
*
* @return pointer to the Heap

* @errors: return null if we have a problem with allocation of heap
			return null if we have a null pointer of vector
*		   
**/
Heap* HeapBuild(Vector* _vec);/*O(n)*/

/**
* @function: HeapDestroy
* @brief destroy the heap but not the vector
* 
* @param _heap: a pointer to the heap that i want to desroy
*
* @return no return value
*		   
**/
void HeapDestroy(Heap* _heap);

/**
* @function: HeapInsert
* @brief insert data to the heap from the bottom to the apropriate place
* 
* @param _heap: a pointer to the heap that i want add item
* @param __data: the data i want to add to the heap

* @return ERR_OK if every thing goes well

* @errors: return ERR_UNINITIALIZED if we have a null pointer to heap
			return ERR_ADD_MISS if we didnt manage to add element to the heap  
*		   
**/
ADTErr HeapInsert(Heap* _heap, int _data);

/**
* @function: HeapMax
* @brief get the max of the heap
* 
* @param _heap: a pointer to the heap
* @param __data: the max of the heap

* @return ERR_OK if every thing goes well

* @errors: return ERR_UNINITIALIZED if we have a null pointer to heap
		 
*		   
**/
ADTErr HeapMax(Heap* _heap, int* _data);

/**
* @function: HeapExtractMax
* @brief remove the max from the heap and fix the heap
* 
* @param _heap: a pointer to the heap
* @param __data: the max of the heap

* @return ERR_OK if every thing goes well

* @errors: return ERR_UNINITIALIZED if we have a null pointer to heap or we have a null pointer of _data
		 
*		   
**/
ADTErr HeapExtractMax(Heap* _heap, int* _data);

/**
* @function: HeapItemsNum
* @brief get the number of item in the heap
* 
* @param _heap: a pointer to the heap

* @return: if null pointer return -1
			return numbers of element in the heap

		 
*		   
**/
int HeapItemsNum(Heap* _heap);

/**
* @function: HeapItemsPrint
* @brief print the element of the heap
* 
* @param _heap: a pointer to the heap
		 
*		   
**/
void HeapItemsPrint(Heap* _heap);

#endif/*__HEAP_H__*/
