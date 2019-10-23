#include "QMan.h"

#include <pthread.h> 	/* pthread_t 	*/
#include <stdlib.h>  	/* malloc 		*/
#include <sys/types.h>	/* ftok 		*/
#include <sys/ipc.h>	/* ftok 		*/
#include <sys/stat.h> 	/* S_IRUSR 		*/
#include <sys/msg.h> 	/* msgget 		*/
#include <string.h>     /* memcpy 		*/

#include "subAgg.h"
#include "zlog4c.h"
#include "cdr.h"
#include "Subscriber.h"

#define PAUSE 			-1
#define PERMS 			IPC_CREAT|S_IRUSR | S_IWUSR
#define GENERAL_CHANNEL 1
#define SIN_SIZE 		sizeof(pid_t) + 1
#define MAX_BUFFER 		1024
#define CHANNEL_RETURN  2 

struct mbuf /*TODO optimize with msgbuf*/
{
	long m_type;
	char m_text[SIN_SIZE];
};

struct QMan
{
	SubAgr* m_agg;
	char*   m_filename;
	char    m_protocle;
};

struct msgbuf 
{
	long mtype;
	char mtext[1];
};



typedef struct QContext
{
	pid_t  	m_pidUI;
	SubAgr* m_subAgg;
	int 	m_msqid;	
}QContext;

/*####################################################*/
static int 			Create_Mq(char* _filename, char _protocole);
static int 			dispatchUI(QMan* _qman, int msqid);
static void 		deleteMq(int msqid);
static QContext* 	QContext_Create(QMan* _qman , pid_t _pid, int _msqid);
static void 		CreateThread(QContext* _context);
static void* 		run_Thread(void* _context);
static PairChannel* PairChannel_Create(pid_t _pid);
static void 		send(PairChannel* _channels, int _msqid);
static Request*  	receiveRequest( PairChannel* _pairChannel,int msqid);
static Request*		receiveMessage(PairChannel* _pairChannel, int _msqid, Request* _request);
static void   		sendAck(PairChannel* _channels,int  _msqid);
static void 		answerRequest(PairChannel* _channels, QContext* _qContext,Request* res);
static void 		QContext_Destroy(QContext* _qContext);
static void 		PairChannel_Destroy(PairChannel* _channels);
static Request* 	Request_create();
static void 		answerQuery(Request* _req, QContext* _qContext,PairChannel* _channels);
static void 		answerFinish(Request* _req, PairChannel* _channels, QContext* _qContext);
static void 		sendSub(PairChannel* _channels, Subscriber* _sub, int _msqid); /*TODO merge with sendAck*/
/*#####################################################*/
QMan* QManStruct_Create(SubAgr* _subAgg, char* _filename,char _protocole)
{
	QMan* newQman = NULL;

	newQman = (QMan*)malloc(sizeof(QMan));
	if(NULL == newQman)
	{
		return NULL;
	}
	newQman -> m_filename = malloc(sizeof(char)* strlen(_filename));
	strcpy(newQman -> m_filename, _filename);
	newQman -> m_agg = _subAgg;
	newQman -> m_protocle = _protocole;

	return newQman;
}

void* QMan_Run(void* _qman)
{
	int msqid 	= 0;
	int res 	= 0;

	ZLOG(LOG_TRACE, "run query manager");
	msqid = Create_Mq(((QMan*)_qman)-> m_filename, ((QMan*)_qman)-> m_protocle);
	ZLOG(LOG_TRACE,"msqid = %d",msqid);

	while(1)
	{
		res = dispatchUI(((QMan*)_qman), msqid);
		if(res == PAUSE)
		{
			break;
		}
	}

	ZLOG(LOG_TRACE,"delete message queue");
	deleteMq(msqid);
	return  NULL;
}
/*########################################################*/

static int Create_Mq(char* _filename, char _protocole)
{
	key_t key = 0;
	int msqid = 0;
	
	key = ftok(_filename, _protocole);
	if(key == -1)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO GET KEY");
	}

	msqid = msgget(key, PERMS);
	if(msqid < 0)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO GET MESSAGE QUEUE");
		exit(1);
	}
	return msqid;
}

static int dispatchUI(QMan* _qman, int _msqid)
{
	struct mbuf msg ;
	pid_t pidUI 			= 0;
	QContext* newContext 	= NULL;
	
	if(msgrcv(_msqid, &msg, SIN_SIZE, GENERAL_CHANNEL, 0)<0)
	{
		ZLOG(LOG_ERROR, "PROBLEM TO RECEIVE MESSAGE");
		return -1;
	}
	memcpy(&pidUI, msg.m_text, sizeof(int));

	newContext = QContext_Create(_qman, pidUI, _msqid);
	if(NULL == newContext)
	{
		ZLOG(LOG_ERROR, "PROBLEM TO CREATE CONTEXT");
		return -1;
	}

	CreateThread(newContext);
	return 1;
}

static QContext* QContext_Create(QMan* _qman , pid_t _pid, int _msqid)
{
	QContext* newContext = NULL;

	newContext = (QContext*)malloc(sizeof(newContext));
	if(NULL == newContext)
	{
		return NULL;
	}

	newContext -> m_subAgg 	= _qman -> m_agg;
	newContext -> m_pidUI 	= _pid;
	newContext -> m_msqid 	= _msqid; 

	return newContext; 
}

static void CreateThread(QContext* _context)
{
	pthread_t threadUI = 0;
	if(pthread_create(&threadUI, NULL,run_Thread, _context) != 0)
    {
    	ZLOG(LOG_DEBUG, "error on creating a thread");
   	}
}

static void* run_Thread(void* _context)
{
	pid_t pidUI 				= 0;
	Request* res 				= NULL;
	int msqid 					= 0;
	PairChannel* newChannels  	= NULL;

	pidUI = ((QContext*)_context) -> m_pidUI;
	msqid = ((QContext*)_context) -> m_msqid;

	ZLOG(LOG_TRACE , "Create pair of channels");
	newChannels = PairChannel_Create(pidUI);
	if(NULL == newChannels)
	{
		ZLOG(LOG_ERROR, "error Create pair of Channel");
		return NULL;
	}

	send(newChannels, msqid);

	while(1)
	{
		res = receiveRequest( newChannels, msqid);
		if(res == NULL)
		{	
			return NULL;
		}

		answerRequest(newChannels,_context , res);
	}
	PairChannel_Destroy(newChannels);
	QContext_Destroy(_context);
	return NULL;
}


static PairChannel* PairChannel_Create(pid_t _pid)
{
	PairChannel* newChannels = NULL;
	pid_t channelRequest 	 = 0;
	pid_t channelReponse     = 0;

	channelRequest = _pid * 2;
	channelReponse = _pid * 2 + 1;

	ZLOG(LOG_TRACE , "the 2 channels are : %d, %d", _pid * 2, _pid * 2 +1);

	newChannels = (PairChannel*) malloc(sizeof(PairChannel));
	if(NULL == newChannels)
	{
		return NULL;
	}
	newChannels -> m_request = channelRequest;
	newChannels ->m_response = channelReponse;

	return newChannels;
}

static void send(PairChannel* _channels, int _msqid)
{
	struct  msgbuf *pmsg;
	char buff[MAX_BUFFER];

	pmsg = (struct msgbuf*)buff;
	pmsg -> mtype = CHANNEL_RETURN;
	memcpy(pmsg -> mtext , _channels, sizeof(PairChannel));
	
	
	memcpy(pmsg -> mtext,_channels,sizeof(PairChannel));
	ZLOG(LOG_DEBUG, "send PairChannel to channel");

	if(msgsnd(_msqid,pmsg,sizeof(PairChannel),IPC_NOWAIT) < 0)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO SEND TO RETURN CHANNEL");
	}
	/*sendAck(_channels, _msqid);*/
}

static Request*  receiveRequest(PairChannel* _pairChannel,int _msqid)
{
	Request* newRequest = Request_create();/*TODO*/
	if(NULL == newRequest)
	{
		ZLOG(LOG_ERROR, "ERROR CREATING REQUEST STRUC");
		return NULL;
	}

	receiveMessage(_pairChannel, _msqid, newRequest);
	return newRequest;
	
}

static Request*	receiveMessage(PairChannel* _pairChannel, int _msqid, Request* _request)
{
	char buff[MAX_BUFFER];
	struct msgRequest msgreq;

	/*msgreq = (struct msgRequest*)buff;*/
	
	
	if(msgrcv(_msqid, &msgreq, sizeof(MAX_BUFFER), _pairChannel -> m_request, MSG_NOERROR)<0)
	{
		ZLOG(LOG_ERROR, "PROBLEM TO RECEIVE REQUEST");
		return NULL;
	}
	
	(_request) -> m_IMSI = msgreq.m_IMSI;
	(_request) -> m_type = msgreq.m_req;
	
	ZLOG(LOG_TRACE, "i receive a request: %d", (_request) -> m_type);

	return _request;

}

static Request* Request_create()
{
	Request* newRequest = (Request*)malloc(sizeof(Request));
	return newRequest;
}

static void sendAck(PairChannel* _channels,int  _msqid)
{
	struct  msgbuf *pmsg;
	char buff[MAX_BUFFER];
	RequestType type = ACK;
	pmsg = (struct msgbuf*)buff;
	pmsg -> mtype = _channels -> m_response;

	memcpy(pmsg -> mtext, &type, sizeof(type));
	ZLOG(LOG_DEBUG, "send PairChannel to channel");
	if(msgsnd(_msqid,pmsg,sizeof(type),IPC_NOWAIT) < 0)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO SEND ACK");
	}
}

static void answerRequest(PairChannel* _channels, QContext* _qContext,Request* _req)
{
	switch(_req -> m_type)
	{
		case QUERY:
			answerQuery(_req, _qContext, _channels);/*TODO*/
			break;
		
		case FIN:
			answerFinish(_req,_channels, _qContext);/*TODO cancel and set param to exit immediatly*/ 
			break;

		default:/*TODO*/
			break;
	}
}

static void PairChannel_Destroy(PairChannel* _channels)
{
	ZLOG(LOG_TRACE, "delete struct of channels id");
	free(_channels);
}

static void QContext_Destroy(QContext* _qContext)
{
	ZLOG(LOG_TRACE, "delete struct of context");
	free(_qContext);
}

static void deleteMq(int _msqid)
{
	msgctl(_msqid,IPC_RMID,NULL);
	ZLOG(LOG_TRACE, "delete message queue");
}

static void answerQuery(Request* _req, QContext* _qContext, PairChannel* _channels)
{
	int key = 0;
	int size = 0;
	Subscriber* copySub ;

	size = Subscriber_Size();

	key = _req -> m_IMSI;
	copySub = (Subscriber*) malloc(size);
	if(NULL == copySub)
	{
		return;
	}

	if(SubAgr_getQuery(_qContext -> m_subAgg , &key,copySub) != SUBAGR_SUCCESS)
	{
		copySub -> m_IMSI = 0;
	}

	sendSub(_channels, copySub, _qContext -> m_msqid);
}

static void answerFinish(Request* _req, PairChannel* _channels, QContext* _qContext)
{
	sendAck(_channels, _qContext -> m_msqid);
	pthread_t self = 0;
	self = pthread_self();
	pthread_cancel(self);
}

static void sendSub(PairChannel* _channels, Subscriber* _sub, int _msqid)
{
	struct  mesSub *pmsg;
	char buff[MAX_BUFFER];
	int size = Subscriber_Size();
	
	pmsg = (struct mesSub*)buff;
	pmsg -> m_type = _channels -> m_response;
	memcpy(&(pmsg -> m_sub), _sub, size);
	
	ZLOG(LOG_DEBUG, "send response to channel");

	if(msgsnd(_msqid,buff,size,IPC_NOWAIT) < 0)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO SEND response");
	}
}
