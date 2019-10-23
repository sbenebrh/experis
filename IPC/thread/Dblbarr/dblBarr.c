#include "dblBarr.h"

#include <stdlib.h>
#include <pthread.h>
struct dblBarr
{
	pthread_barrier_t m_firstbarrier;
	pthread_barrier_t m_secondbarrier;
	size_t			  m_numberOfthread;
	sem_t			  m_sem;
};

dblBar* dblBarr_Create(size_t _count)
{
	dblBar* newdblBar = NULL;

	if(_count == 0)
	{
		return NULL;
	}
	newdblBar = (dblBar*)malloc(sizeof(dblBar));
	if(NULL == newdblBar)
	{
		return NULL;
	}
	if(pthread_barrier_init(&(newdblBar -> m_firstbarrier),0,_count) != 0)
	{
		free(newdblBar);
		return NULL;
	}
	if(pthread_barrier_init(&(newdblBar -> m_secondbarrier),0,_count) != 0)
	{
		free(newdblBar);
		return NULL;
	}
	newdblBar -> m_numberOfthread = _count;
	sem_init(&(newdblBar -> m_sem), 0, _count);
	return newdblBar;
} 

void dblBarr_Destroy(dblBar** _dblbarr)
{
	if(_dblbarr == NULL || *_dblbarr == NULL)
	{
		return;
	}
	pthread_barrier_destroy(&(_dblbarr -> m_barrier));
	free(_dblbarr);
}

int dblBarrWait(dlbBar* _db, void*(*_func)(void*), void* _arg)
{
	if(NULL == _db)
	{
		return;
	}
	sem_wait(&(newdblBar -> m_sem));
	if(pthread_barrier_wait(&(_db -> m_firstbarrier)) != 0)
	{
		return FAIL;
	}

	if(_func != NULL)
	{
		_func(_arg);
	}
	sem_post(&(newdblBar -> m_sem));
	if(pthread_barrier_wait(&(_db -> m_secondbarrier)) != 0)
	{
		return FAIL;
	}
	return SUCCEES;
}