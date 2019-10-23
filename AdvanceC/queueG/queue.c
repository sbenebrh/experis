#include<stdlib.h>
#include"queue.h"

#define CHECKNULLPOINTER(X)		if(NULL == X) return NULL;
#define CHECKPOINTER(X)			if(NULL == X) return QUEUE_UNINITIALIZED_ERROR;

#define ITEMS(X) 		(X) -> m_items
#define NITEMS(X) 		(X) -> m_nitems
#define SIZE(X) 		(X) -> m_size
#define HEADINDEX(X) 	(X) -> m_head
#define TAILINDEX(X) 	(X) -> m_tail

 struct  Queue
{
	size_t 		m_size;
	void* *     m_items;
	size_t 		m_nitems;
	size_t 		m_head;
	size_t		m_tail;
};

/*###############STATICS FUNCTIONS##############################*/
static void 	InitializeQueue(Queue* _queue,size_t _maxSize);
static void 	DestroyInsideElement(Queue* _queue, void (*_elementDestroy)(void* _item));
static int 		IsFull(Queue* _queue);
static void 	moveNext(Queue* _queue,int flag);
static int 		IsAtEnd(Queue* _queue);
/*#############################################################*/

Queue* Queue_Create(size_t _maxSize)
{
	Queue* newQueue = NULL;
	if(_maxSize > 0)
	{
		newQueue = (Queue*) malloc(sizeof(Queue));
		CHECKNULLPOINTER(newQueue);

		InitializeQueue(newQueue,_maxSize);
		if(!ITEMS(newQueue))
		{
			free(newQueue);
			return NULL;
		}	
	}
	return newQueue;
}

void Queue_Destroy(Queue** _queue, void (*_elementDestroy)(void* _item))
{
	if(NULL == _queue || NULL == *_queue)
	{
		return;
	}

	DestroyInsideElement(*_queue, (*_elementDestroy));

	free(ITEMS(*_queue));
	free(*_queue);
	*_queue = NULL;
}


Queue_Result Queue_Enqueue(Queue* _queue, void* _item)
{
	CHECKPOINTER(_queue);
	if(IsFull(_queue))
	{
		return QUEUE_OVERFLOW;
	}

	ITEMS(_queue)[TAILINDEX(_queue)] = _item;
	
	moveNext(_queue,1);
	
	NITEMS(_queue) += 1;

	return QUEUE_SUCCESS;
}

Queue_Result Queue_Dequeue(Queue* _queue, void** _pValue)
{
	CHECKPOINTER(_queue);
	CHECKPOINTER(_pValue);

	if(Queue_IsEmpty(_queue))
	{
		return QUEUE_UNDERFLOW;
	}

	*_pValue = ITEMS(_queue)[HEADINDEX(_queue)];	
	moveNext(_queue, 0);
	NITEMS(_queue) -= 1;

	return QUEUE_SUCCESS;
}

int Queue_IsEmpty(const Queue* _queue)
{
	if(!_queue)
	{
		return FALSE;
	}
	return !NITEMS(_queue);	
}
/*#############################################################*/

static void InitializeQueue(Queue* _queue,size_t _maxSize)
{
	SIZE(_queue) = _maxSize;
	NITEMS(_queue) = 0;
	HEADINDEX(_queue) = 0;
	TAILINDEX(_queue) = 0;
	ITEMS(_queue) = (void**) malloc(_maxSize * sizeof(void*));
}

static void DestroyInsideElement(Queue* _queue, void (*_elementDestroy)(void* _item))
{
	int lastIndex = HEADINDEX(_queue);
	int i;

	if(_elementDestroy)
	{
		for(i = TAILINDEX(_queue); i != lastIndex; ++i)
			i = i % SIZE(_queue);
		(*_elementDestroy)(ITEMS(_queue)[i]);	
	}
}

static int IsFull(Queue* _queue)
{
	return NITEMS(_queue) == SIZE(_queue);
}

static void moveNext(Queue* _queue,int flag)
{
	if(flag)
	{
		  if(IsAtEnd(_queue))
		  {
		  	TAILINDEX(_queue) = 0;
		  }
		  else 	
		  {
		  		TAILINDEX(_queue) += 1;
		  }
	}
	else
	{
		if(IsAtEnd(_queue))
		{
		  	HEADINDEX(_queue) = 0;
		}
		else 
		{
		 	HEADINDEX(_queue) += 1;
		}
	}
		
}

static int IsAtEnd(Queue* _queue)
{
	return TAILINDEX(_queue) == SIZE(_queue) -1;
}
