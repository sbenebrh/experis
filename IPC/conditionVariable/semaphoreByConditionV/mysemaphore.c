#include "mysemaphore.h"

#include <pthread.h>

struct Mysemaphore
{
	size_t 			m_value;
	pthread_mutex_t m_lock;
	pthread_cond_t	m_cond;
};
/*##############################################################*/
static int 	initialiseStruct(Mysemaphore* _semaphore,size_t _val);
static void destoy_mutexs(Mysemaphore* _semaphore);
/*##############################################################*/


Mysemaphore* Semaphore_Create(size_t _val)
{
	Mysemaphore* newSemaphore = NULL;

	newSemaphore = (Mysemaphore*) malloc(sizeof(Mysemaphore));
	if(NULL == newSemaphore)
	{
		return NULL;
	}
	if(initialiseStruct(newSemaphore,_val) != 0)
	{
		free(newSemaphore);
		return NULL;
	}
	return newSemaphore;
}

void Semaphore_Destroy(Mysemaphore **_semaphore)
{
	if(NULL == _semaphore || NULL == *_semaphore)
	{
		return;
	}
	destoy_mutexs(*_semaphore);

	free(*_semaphore);
	*_semaphore = NULL;
	
}

int Up(Mysemaphore* _semaphore)
{
	if(pthread_mutex_lock(&(_semaphore->m_lock)) != 0)
	{
		return FAIL;
	}
    _semaphore->m_value++;
    if(pthread_cond_signal(&(_semaphore->m_cond)) != 0)
    {
    	return FAIL;
    } 
    
   	if(pthread_mutex_lock(&(_semaphore->m_lock)) != 0)
	{
		return FAIL;
	}
}

int Down(Mysemaphore* _semaphore)
{
	if(NULL == _semaphore)
	{
		return FAIL;
	}
	if(pthread_mutex_lock(&(_semaphore->m_lock)) != 0)
	{
		return FAIL;
	}
    while (_semaphore-> m_value == 0) 
    {
        if(pthread_cond_wait(&(_semaphore->m_cond), &(_semaphore->m_lock)) != 0)
        {
        	return FAIL;
        } 
    }
    _semaphore->m_value--;

   if(pthread_mutex_lock(&(_semaphore->m_lock)) != 0)
	{
		return FAIL;
	}
}


/**************************************************************************************/
static int initialiseStruct(Mysemaphore* _semaphore, size_t _val)
{
	if(pthread_mutex_init(&(_semaphore -> m_lock), NULL) != 0)
	{
		return FAIL;
	}
	_semaphore -> m_value = _val;
	return pthread_cond_init(&(_semaphore -> m_cond), NULL); 
}

static void destoy_mutexs(Mysemaphore* _semaphore)
{
	pthread_cond_destroy(&(_semaphore -> m_cond));
	pthread_mutex_destroy(&(_semaphore -> m_lock));
}