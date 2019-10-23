#include "producer.h"

#include <pthread.h>
#include <stdlib.h>

#include "wQueue.h"
#define BUFF_SIZE	100
struct Producers
{
	size_t     m_numbers;
	pthread_t*  m_threads;
};

static int nums[BUFF_SIZE];
/*####################STATICS DECLA #########################*/
static void Create_Threads(Producers* _producers,WQueue* _wqueue);
static void fill_num_buff(void);
/*##########################################################*/
Producers* create_producers(size_t numbers,WQueue* _wqueue)
{
	size_t i = numbers;
	Producers* newProducers = NULL;

	newProducers = (Producers*)malloc(sizeof(Producers));
	if(NULL == newProducers)
	{
		perror("allocation");
		return NULL;
	}
	newProducers -> m_numbers = numbers;
	newProducers -> m_threads = (pthread_t*) malloc(numbers * sizeof(pthread_t));
	if(NULL == newProducers -> m_threads)
	{
		perror("allocation");
		free(newProducers);
		return NULL;
	}
	Create_Threads(newProducers,_wqueue);
	fill_num_buff();
	return newProducers;

}

void join_producers(Producers* _producers)
{
	int i = 0;
	int producers = _producers -> m_numbers;
	for ( i ; i < producers; ++i)
	{
		if(pthread_join(_producers -> m_threads[i],NULL) != 0)
  		{
  			perror("join");
  			exit(1);
  		}
	}
}

void* run_producer(void* _arg)
{
	static int i = 0;
	WQueue_Enqueue((WQueue*) _arg, &nums[i]);
	i++;
}
void Destroy_producers(Producers** _producers)
{
	free((*_producers) -> m_threads);
	free(*_producers);
	*_producers = NULL;
}
/************************************************************************/
static void Create_Threads(Producers* _producers, WQueue* _wqueue)
{
	int i = 0;
	int producers = _producers -> m_numbers;
	for(i; i < producers; ++i)
	{
		if(pthread_create(&(_producers -> m_threads[i]),NULL, run_producer, _wqueue) != 0)
    	{
    		perror("create thread");
    		exit(1);
   		}
	}
}

static void fill_num_buff(void)
{
	int i = 0;
	for (; i < BUFF_SIZE;++i)
	{
		nums[i] = i;
	}
}