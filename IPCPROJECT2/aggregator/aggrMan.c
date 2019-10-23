#include "aggrMan.h"

#include <pthread.h> 		/*pthread_t 	*/
#include <stdlib.h>			/*malloc   		*/
#include <sys/msg.h> 		/* msgget		*/
#include <sys/stat.h> 		/* S_IRUSR		*/

#include "ConcurentHash.h" 	/*ConcurentHash	*/
#include "zlog4c.h"			/*zlog_init		*/
#include "cdr.h" 			/*cdr 			*/
#include "subAgg.h" 		/*subAgg 		*/

#define PERMS 			S_IRUSR | S_IWUSR
#define TRUE 			1
#define FALSE 			0
#define RTOAG 			1
#define BUFF_SIZE       512

struct AggrMan
{
	SubAgr* 		m_subAggr;
	int 			m_numberOfThreads;
	pthread_t* 		m_threads;
	int 			m_msqid;
};

struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    char mtext[1];    /* message data */
};
/*#####################################################################*/
static void* 	initStruct(AggrMan* _agg, size_t _numberOfThreads, SubAgr* _subaggr);
static int 		rattachToChannel(char* _filename, char _protocole);
static void* 	run_agg(void* _context);
static void 	DestroyThreads(AggrMan*_agg);
/*####################################################################*/

AggrMan* AggrMan_Create(size_t _numberOfThreads,SubAgr* _subaggr, char* _filename, char _protocole)
{
	AggrMan* newAggr 	= NULL;
	void* res 			= NULL;

	/*zlog_init("logconfig");*/
	ZLOG(LOG_TRACE, "create aggregator");

	newAggr = (AggrMan*) malloc(sizeof(AggrMan));
	if(NULL == newAggr)
	{
		ZLOG(LOG_DEBUG, "impossible to allocate for newAggr");
		return NULL;
	}

	ZLOG(LOG_TRACE, "attach to channel");
	newAggr -> m_msqid = rattachToChannel(_filename, _protocole);
	if(newAggr -> m_msqid < 0)
	{
		free(newAggr);
		return NULL;
	}

	res = initStruct(newAggr, _numberOfThreads, _subaggr);
	if(NULL == res)
	{
		free(newAggr);
		return NULL;
	}
	return newAggr;
}	

void AggrMan_Destroy(AggrMan** _pAgg)
{
	DestroyThreads(*_pAgg);
	free(*_pAgg);
	*_pAgg = NULL;
}
/*####################################################################*/
static void* initStruct(AggrMan* _agg, size_t _numberOfThreads,SubAgr* _subaggr)
{
	int i 		= 0;

	_agg -> m_numberOfThreads = _numberOfThreads;
	_agg -> m_threads = (pthread_t*) malloc(_numberOfThreads * sizeof(pthread_t));
	if(NULL == _agg -> m_threads)
	{
		ZLOG(LOG_DEBUG, "impossible to allocate for m_threads");
		return NULL;
	}	

	_agg -> m_subAggr = _subaggr;

	ZLOG(LOG_TRACE, "begining creation of threads");
	for(i = 0 ;i < _numberOfThreads ; ++i)
	{
		if(pthread_create(&(_agg -> m_threads[i]),NULL, run_agg, _agg) != 0)
    	{
    		ZLOG(LOG_DEBUG, "error on creating a thread");
   		}
	}
	return _agg -> m_subAggr;
}

static int rattachToChannel(char* _filename, char _protocole)
{
	key_t key = 0;
	int msqid = 0;

	key = ftok(_filename, _protocole);
	if(key == -1)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO GET KEY");
	}
	
	ZLOG(LOG_DEBUG, "the key is : %d",key);

	msqid = msgget(key, PERMS);
	if(msqid < 0)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO ATTACH TO CHANNEL");
	}

	return msqid;
}

static void* run_agg(void* _context)
{
	char buf[BUFF_SIZE];
	struct  msgbuf *pmsg;
	int msqid = ((AggrMan*)_context )-> m_msqid;
	

	while(1)
	{
		
		if(msgrcv(msqid, buf, sizeof(CDR), RTOAG, 0)<0)
		{
			ZLOG(LOG_ERROR, "PROBLEM TO RECEIVE MESSAGE");
			exit(1);
		}
		ZLOG(LOG_TRACE, "new line");
		
		pmsg = (struct msgbuf*)buf;/*TODO CHECK */
		ZLOG(LOG_TRACE,"message receive");
		SubAgr_update(((AggrMan*)_context) -> m_subAggr,(CDR*)(pmsg -> mtext));
	}
}


/*********************************************************************************/
static void DestroyThreads(AggrMan*_agg)
{
	int i 			= 0;
	int capacity 	= _agg -> m_numberOfThreads;

	ZLOG(LOG_TRACE,"join all threads");
	for(i = 0; i < capacity ; ++i)
	{
		if(pthread_join(_agg -> m_threads[i], NULL) != 0)
		{
			ZLOG(LOG_DEBUG,"impossible to join thread number: %d",i);
		}
	}
	for(i = 0 ; i < capacity;++i)
	{
		if(pthread_cancel(_agg -> m_threads[i]) != 0)
		{
			ZLOG(LOG_DEBUG,"impossible to cancel thread number: %d",i);
		}
	}
	/*TODO destroy thread*/
	/*use condition variable*/

}
