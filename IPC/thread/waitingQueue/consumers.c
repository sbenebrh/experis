#include "consumers.h"

#include <stdlib.h> /*malloc*/
#include <pthread.h> /*pthread_create*/

#include "wQueue.h"


struct Consumers
{
	size_t     m_numbers;
	pthread_t*  m_threads;
};
/*##############STATIC##############################*/
static void Create_Threads(Consumers* _consumers, WQueue* _wqueue);
/*#################################################*/

Consumers* Create_Consumers(size_t _numbers, WQueue* _wqueue)
{
	size_t i = _numbers;
	Consumers* newConsumers = NULL;

	newConsumers = (Consumers*)malloc(sizeof(Consumers));
	if(NULL == newConsumers)
	{
		perror("allocation");
		return NULL;
	}
	newConsumers -> m_numbers = _numbers;
	newConsumers -> m_threads = (pthread_t*) malloc(_numbers * sizeof(pthread_t));
	if(NULL == newConsumers -> m_threads)
	{
		perror("allocation");
		free(newConsumers);
		return NULL;
	}

	Create_Threads(newConsumers,_wqueue);
	return newConsumers;
}

void join_Consumers(Consumers* _consumers)
{
	int i = 0;
	int consumers = _consumers -> m_numbers;
	for ( i ; i < consumers; ++i)
	{
		if(pthread_join(_consumers -> m_threads[i],NULL) != 0)
  		{
  			perror("join");
  			exit(1);
  		}
	}
}
void* run_Consumer(void* _arg)
{
	int * a;
	WQueue_Dequeue((WQueue*) _arg,(void**) &a);
	printf("%d\n",*a );
}
void kill_Consumers(Consumers* _consumers)
{
	int i = 0;
	int consumers = _consumers -> m_numbers;
	for ( i ; i < consumers; ++i)
	{
		if(pthread_cancel(_consumers -> m_threads[i]) != 0)
  		{
  			perror("join");
  			exit(1);
  		}
	}
}
void Destroy_Consumers(Consumers** _consumers)
{
	free((*_consumers) -> m_threads);
	free(*_consumers);
	*_consumers = NULL;
}

/******************************************************************************/

static void Create_Threads(Consumers* _consumers,WQueue* _wqueue)
{
	int i = 0;
	int consumers = _consumers -> m_numbers;
	for(i; i < consumers; ++i)
	{
		if(pthread_create(&(_consumers -> m_threads[i]),NULL, run_Consumer, _wqueue) != 0)
    	{
    		perror("create thread");
    		exit(1);
   		}
	}
}