
/*
 * queue.h
 * framework for queue
 * Version: 1.0
 * creation: 13/12/2018
 * last change: 13/12/2018
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
*/


#ifndef _QUEUE_H
#define _QUEUE_H
#include"ADTErr.h" 


typedef struct Queue Queue;

/** 
 * @function: QueueCreate
 * create a static queue for integer
 * and every needed information about it 
 *
 * @param _size : the size of the queue 
 
 * @return return pointer to the queue
 * 			if size < = 0 return NULL
 *			if the queue was not propely created  NULL
 *			
 **/
Queue* QueueCreate(size_t _size);

/** 
 * @function: QueueDestroy	
 * @brief: destroy the queue if it exist
 * 
 * @param _queue : pointer to the queue generated by QueueCreate
 *
 * @return no return value
**/
void QueueDestroy(Queue* _queue);

/**
* @function: QueueInsert
* @brief add the data element at the to the place that point the tail pointer and fix the tail to the next free place if exist
* 
*
* @param * _queue : pointer to queue generated by QueueCreate
* @param _item : the data to add 
* 
*
* @return the status of adding the data ERR_OK

* @errors: return ERR_UNINITIALIZE if their is no allocation for the queue 
*          return ERR_OVERFLOW if their is no more room in the queue  
*		   
**/
ADTErr QueueInsert(Queue* _queue, int _item);

/**
* @function: QueueRemove 
* remove the element that the pointer head points 
* fix the position of the head pointer to the next to be remove
*
* @param * _queue : pointer to the queue generated by QueueCreate
* @param _item : the removed data
*
* @return the status of the operation ERR_OK

* @errors: return ERR_UNINITIALIZE if their is no allocation for the queue
* 		   return ERR_EMPTY_ARRAY if the queue is empty	
*		   	 	
**/
ADTErr QueueRemove(Queue* _queue, int* _item);

/**
* @function: IsEmpty 
* check is the queue is empty
* fix the position of the head pointer to the next to be remove
*
* @param * _queue : pointer to the queue generated by QueueCreate

*
* @return true if the queue is empty else false

**/
int IsEmpty(const Queue* _queue);


int QueuePrint(const Queue* _Queue);

#endif/*_QUEUE_H*/
