#include<stdio.h>
#include<stdlib.h>
#include"ADTErr.h"
#include"queue.h"
#define MAGIC_NUMBER 0xBEEFBEEF
#define NO_MAGIC_NUMBER 0xDEADBEEF

#define MAGICNUMBER(X) 	(X) -> m_magicNumber
#define ITEMS(X) 		(X) -> m_items
#define NITEMS(X) 		(X) -> m_nitems
#define SIZE(X) 		(X) -> m_size
#define HEADINDEX(X) 	(X) -> m_head
#define TAILINDEX(X) 	(X) -> m_tail
#define TRUE 	0
#define FALSE !TRUE 
/*TODO 

moveNext
enum:
ERR_NO_ORIGINAL_POINTER
ERR_UNDERFLOW
ERR_UNITIALIZED*/
 struct  Queue
{
	size_t m_magicNumber;
	size_t m_size;
	int* m_items;
	size_t m_nitems;
	size_t m_head;
	size_t m_tail;
};

void initializeQueue(Queue* _queue,size_t _size)
{	
	MAGICNUMBER(_queue) = MAGIC_NUMBER;
	SIZE(_queue) = _size;
	NITEMS(_queue) = 0;
	HEADINDEX(_queue) = 0;
	TAILINDEX(_queue) = 0;
	ITEMS(_queue) = (int*) malloc(_size * sizeof(int));
}
void moveNext(Queue* _queue,int flag)
{
	if(flag)
	{
		  if(TAILINDEX(_queue) == SIZE(_queue) -1)
		  	TAILINDEX(_queue) = 0;
		  else 	TAILINDEX(_queue) += 1;
		
	}
	else
	{
		if(HEADINDEX(_queue) == SIZE(_queue) -1)
		  	HEADINDEX(_queue) = 0;
		 else 	HEADINDEX(_queue) += 1;
	}
		
}
Queue* QueueCreate(size_t _size)
{
	Queue* newQueue = NULL;
	if(_size > 0)
	{
		newQueue = (Queue*) malloc(sizeof(Queue));
		if(newQueue)
		{
			initializeQueue(newQueue, _size);
		}
		if(!ITEMS(newQueue))
		{
			free(newQueue);
			return NULL;
		}	
	}
	return newQueue;
}

void QueueDestroy(Queue* _queue)
{
	if(_queue || MAGICNUMBER(_queue) == MAGIC_NUMBER)
	{
		MAGICNUMBER(_queue) = NO_MAGIC_NUMBER;
		free(ITEMS(_queue));
		free(_queue);
	}	
}		
	
ADTErr QueueInsert(Queue* _queue, int _item)
{ 
	if(!_queue) return NOT_INITIALIZED;
	if(MAGICNUMBER(_queue) != MAGIC_NUMBER)
	{
		return ERR_NO_ORIGINAL_POINTER;
	}
	if(NITEMS(_queue) == SIZE(_queue))
	{
		return ERR_OVERFLOW;
	}
	
	ITEMS(_queue)[TAILINDEX(_queue)] = _item;
	
	moveNext(_queue,1);
	
	NITEMS(_queue) += 1;
	
	return ERR_OK;
}

ADTErr QueueRemove(Queue* _queue, int* _item)
{
	if(!_queue) return ERR_UNINITIALIZED;
	if(MAGICNUMBER(_queue) != MAGIC_NUMBER)
	{
		return ERR_NO_ORIGINAL_POINTER;
	}
	
	if(!NITEMS(_queue))
	{
		return ERR_UNDERFLOW;
	}
	if(_item)
		*_item = ITEMS(_queue)[HEADINDEX(_queue)];
	
	 moveNext(_queue, 0);
	 NITEMS(_queue) -= 1;
	
	return ERR_OK;
}
		
int IsEmpty(const Queue* _queue)
{
	if(!_queue)
		return FALSE;
	return !NITEMS(_queue);		
		
}		
		
		
		
		
		
		
		
	
