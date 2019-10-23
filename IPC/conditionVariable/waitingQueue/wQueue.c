#include"wQueue.h"

#include<stdlib.h> /*malloc*/
#include <pthread.h> /*mutex*/
#include <semaphore.h> /*sem_t*/
#include <unistd.h> /*perror*/
#include <stdio.h> /*perror*/

#define CHECKNULLPOINTER(X)		if(NULL == X) return NULL;
#define CHECKPOINTER(X)			if(NULL == X) return ;

#define ITEMS(X) 		(X) -> m_items
#define NITEMS(X) 		(X) -> m_nitems
#define SIZE(X) 		(X) -> m_size
#define HEADINDEX(X) 	(X) -> m_head
#define TAILINDEX(X) 	(X) -> m_tail

 struct  WQueue
{
	size_t 			m_size;
	void			**m_items;
	size_t 			m_nitems;
	size_t 			m_head;
	size_t			m_tail;
	pthread_cond_t 	m_cond;
	pthread_mutex_t m_lock;
};

/*###############STATICS FUNCTIONS##############################*/
static void 	InitializeQueue(WQueue* _wqueue,size_t _maxSize);
static void		initSemaphore(WQueue* _wqueue);
static void 	DestroyInsideElement(WQueue* _wqueue, void (*_elementDestroy)(void* _item));
static void 	DestroySemaphores(WQueue* _wqueue);
static void 	moveNext(WQueue* _wqueue,int flag);
static int 		IsAtEnd(WQueue* _wqueue);
static void		Qwrite(WQueue* _wqueue,void* _item);
static void 	Qread(WQueue* _wqueue,void **_pValue);
/*#############################################################*/

WQueue* WQueue_Create(size_t _maxSize)
{
	WQueue* newWQueue = NULL;
	if(_maxSize > 0)
	{
		newWQueue = (WQueue*) malloc(sizeof(WQueue));
		CHECKNULLPOINTER(newWQueue);

		InitializeQueue(newWQueue,_maxSize);
		if(!ITEMS(newWQueue))
		{
			free(newWQueue);
			return NULL;
		}	
		initSemaphore(newWQueue);
	}
	return newWQueue;
}

void WQueue_Destroy(WQueue** _wqueue, void (*_elementDestroy)(void* _item))
{
	if(NULL == _wqueue || NULL == *_wqueue)
	{
		return;
	}

	DestroyInsideElement(*_wqueue, (*_elementDestroy));
	DestroySemaphores(*_wqueue);
	free(ITEMS(*_wqueue));
	free(*_wqueue);
	*_wqueue = NULL;
}

void WQueue_Enqueue(WQueue* _wqueue, void* _item)
{
	CHECKPOINTER(_wqueue);

	pthread_mutex_lock(&(_wqueue -> m_lock));
	while(_wqueue -> m_nitems == _wqueue -> m_size)
	{
		if(pthread_cond_wait(&(_wqueue ->m_cond), &(_wqueue -> m_lock))!=0)
		{
		perror("cond");
		}
	}
	Qwrite(_wqueue,_item);

	pthread_cond_signal(&(_wqueue->m_cond));
     
	pthread_mutex_unlock(&(_wqueue -> m_lock));
}

void WQueue_Dequeue(WQueue* _wqueue, void** _pValue)
{
	CHECKPOINTER(_wqueue);
	CHECKPOINTER(_pValue);

	pthread_mutex_lock(&(_wqueue -> m_lock));
	while(WQueue_IsEmpty(_wqueue))
	{
		if(pthread_cond_wait(&(_wqueue ->m_cond), &(_wqueue -> m_lock))!=0)
		{
		perror("cond2");
		}
	}
	Qread(_wqueue,_pValue);

	pthread_cond_signal(&(_wqueue->m_cond));

	pthread_mutex_unlock(&(_wqueue -> m_lock));
}

void Wqueue_Broadcast(WQueue* _wqueue)
{
	 pthread_cond_broadcast(&(_wqueue->m_cond));
}

int WQueue_IsEmpty(const WQueue* _wqueue)
{
	if(!_wqueue)
	{
		return FALSE;
	}
	return !NITEMS(_wqueue);	
}
/**********************************************************/
static void InitializeQueue(WQueue* _wqueue,size_t _maxSize)
{
	SIZE(_wqueue) = _maxSize;
	NITEMS(_wqueue) = 0;
	HEADINDEX(_wqueue) = 0;
	TAILINDEX(_wqueue) = 0;
	ITEMS(_wqueue) = (void**) malloc(_maxSize * sizeof(void*));
}

static void	initSemaphore(WQueue* _wqueue)
{
	pthread_cond_init(&(_wqueue -> m_cond), NULL);
	pthread_mutex_init(&(_wqueue -> m_lock), NULL);
}

static void DestroyInsideElement(WQueue* _wqueue, void (*_elementDestroy)(void* _item))
{
	int lastIndex = HEADINDEX(_wqueue);
	int i;

	if(_elementDestroy)
	{
		for(i = TAILINDEX(_wqueue); i != lastIndex; ++i)
			i = i % SIZE(_wqueue);
		(*_elementDestroy)(ITEMS(_wqueue)[i]);	
	}
}

static void DestroySemaphores(WQueue* _wqueue)
{
	if(pthread_cond_destroy(&(_wqueue ->m_cond)) != 0)
	{
		perror("pthread_mutex_destroy");
		exit(1);
	}
	if(pthread_mutex_destroy(&(_wqueue ->m_lock)) != 0)
	{
		perror("pthread_mutex_destroy");
		exit(1);
	}
}
static void moveNext(WQueue* _wqueue,int flag)
{
	if(flag)
	{
		  if(IsAtEnd(_wqueue))
		  {
		  	TAILINDEX(_wqueue) = 0;
		  }
		  else 	
		  {
		  		TAILINDEX(_wqueue) += 1;
		  }
	}
	else
	{
		if(IsAtEnd(_wqueue))
		{
		  	HEADINDEX(_wqueue) = 0;
		}
		else 
		{
		 	HEADINDEX(_wqueue) += 1;
		}
	}
		
}

static int IsAtEnd(WQueue* _wqueue)
{
	return TAILINDEX(_wqueue) == SIZE(_wqueue) -1;
}

static void	Qwrite(WQueue* _wqueue,void* _item)
{
	ITEMS(_wqueue)[TAILINDEX(_wqueue)] = _item;
	moveNext(_wqueue,1);
	NITEMS(_wqueue) += 1;
}

static void Qread(WQueue* _wqueue,void **_pValue)
{
	*_pValue = ITEMS(_wqueue)[HEADINDEX(_wqueue)];	
	moveNext(_wqueue, 0);
	NITEMS(_wqueue) -= 1;
}
