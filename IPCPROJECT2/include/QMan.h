#ifndef __QUERY_MAN_H__
#define __QUERY_MAN_H__
#include <pthread.h> /*pthread_t*/

#include "subAgg.h"
#include "Subscriber.h"


typedef struct QMan QMan;


typedef struct PairChannel
{
	pthread_t m_request;
	pthread_t m_response;
}PairChannel;

typedef enum RequestType
{
	QUERY = 0,
	REPORT,
	EXTRACT,
	ACK,
	FIN, 
	PAUSE,
	SHUTDOWN
}RequestType;

struct msgRequest
{
	long m_type;
	size_t m_IMSI;
	RequestType m_req;
};

struct mesSub
{
	long m_type;
	Subscriber m_sub;
};

typedef struct Request
{
	RequestType m_type;
	int         m_IMSI;
}Request;

QMan* QManStruct_Create(SubAgr* _subAgg, char* _filename,char _protocole);
void* QMan_Run(void* _qman);

#endif /*__QUERY_MAN_H__*/