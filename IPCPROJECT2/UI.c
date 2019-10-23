#include <stdio.h> 		/* printf 						*/
#include <sys/types.h> 	/* ftok							*/
#include <sys/ipc.h> 	/* ftok							*/
#include <sys/msg.h> 	/* msgget						*/
#include <sys/stat.h> 	/* S_IRUSR						*/
#include <errno.h>  	/*errno 						*/
#include <unistd.h> 	/* pid_t 						*/

#include "QMan.h" 		/* TODO move struct to commun file 	*/
#include "zlog4c.h"
#include "Subscriber.h"

#define PERMS 			S_IRUSR | S_IWUSR | IPC_CREAT
#define CHANNEL_RETURN  2L
#define FILENAME 		"/home/samuel/work/IPCPROJECT2/files_part/cdro.txt"
#define PROTOCOLE 		'V'
#define MAX_BUFF 		1024
#define GENERAL_CHANNEL 1L

struct msgChannel
{
	long m_type;
	PairChannel m_pc;
};
struct pidchannel
{
	long m_type;
	pid_t m_pid;
};
/*struct msgRequest
{
	long m_type;
	size_t m_IMSI;
	RequestType m_req;
};*/
struct msgbuf 
{
	long mtype;
	char mtext[1];
};
/*####################################################################*/
static int rattachToChannel(char* _filename, char _protocole);
static void getChannels(int _msqid, int* _channelReq, int* _channelResp);
static void sendRequests(int _msqid,int _channel);
static void receiveResponses(int _msqid,int _channel);
static void sendPid(int _msqid);
static RequestType getRequestType();
static int getSubscriberKey();
/*###################################################################*/

int main(int argc, char const *argv[])
{
	int msqid 			= 0;
	int channelRequest 	= 0;
	int channelReponse 	= 0;
	int res 			= 0;

	zlog_init("logconfig");
	msqid = rattachToChannel(FILENAME, PROTOCOLE);

	getChannels(msqid, &(channelRequest), &(channelReponse));

	printf("%s\n","hello welcomme to the billing domain");
	while(1)
	{
		printf("%s\n","what do you want to do\n 1-query\n 2-report\n");
		scanf("%d", &res);
		switch(res)
		{
			case 0:
				sendRequests(msqid, channelRequest);/*TODO*/
				receiveResponses(msqid, channelReponse); /*TODO*/
				break;

			case 1:
			/*TODO report*/
				break;

			default:
				return 0;
		}
	}

	return 0;
} 


/*##################################################################*/
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

static void getChannels(int _msqid, int* _channelReq, int* _channelResp)
{
	char buff[MAX_BUFF];
	struct msgChannel* channels;
	channels = (struct msgChannel*)buff;
	sendPid(_msqid);

	if(msgrcv(_msqid, buff, sizeof(PairChannel), CHANNEL_RETURN, 0)<0)
	{
		ZLOG(LOG_ERROR, "PROBLEM TO RECEIVE MESSAGE:%s", strerror(errno));
		return ;
	}
	*_channelReq = channels -> m_pc.m_request;
	*_channelResp = channels -> m_pc.m_response;
	ZLOG(LOG_TRACE, "key1:%d, key2:%d",*_channelResp, *_channelResp);
}
static void sendPid(int _msqid)
{
	pid_t id = 0;
	char buff[MAX_BUFF];
	struct pidchannel* pidchannel;

	pidchannel = (struct pidchannel*) buff;
	id = getpid();
	ZLOG(LOG_TRACE,"pid:%d", id);

	pidchannel -> m_type = GENERAL_CHANNEL;
	pidchannel -> m_pid = id;

	if(msgsnd(_msqid, pidchannel, sizeof(pid_t), 0))
	{
		ZLOG(LOG_DEBUG, "IMPOSSIBLE TO SEND PID: %s", strerror(errno));
	}
}
static void sendRequests(int _msqid,int _channel)
{
	int key = 0;
	char buff[MAX_BUFF];
	RequestType type;
	struct msgRequest* msgreq;

	msgreq = (struct msgRequest*)buff;

	type = getRequestType();
	switch(type)
	{
		case QUERY:
			key = getSubscriberKey();
			msgreq -> m_req = QUERY;
			msgreq -> m_IMSI = key;
			break;

		case REPORT:/*TODO*/
			break;

		default:/*TODO*/
			break;
	}
	
	msgreq -> m_type = _channel;

	if(msgsnd(_msqid,msgreq,MAX_BUFF,0) < 0)/*maybe send buff*/
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO SEND REQUEST");
	}

	printf("%d\n%d\n", msgreq -> m_req, msgreq -> m_IMSI);
}
static void receiveResponses(int _msqid,int _channel)
{
	char buff[MAX_BUFF];
	struct mesSub* messub;
	int size = 0;

	messub = (struct mesSub*)buff;
	size = Subscriber_Size();
	if(msgrcv(_msqid, buff, size, _channel, 0)<0)
	{
		ZLOG(LOG_ERROR, "PROBLEM TO RECEIVE REQUEST");
		return ;
	}
	if(messub -> m_sub.m_IMSI == 0)
	{
		return;
	}
	printf("%s%ld\n", "the IMSI is :", messub -> m_sub.m_IMSI);

}

static RequestType getRequestType()
{
	return QUERY;
}
static int getSubscriberKey()
{
	int key = 0;
	printf("%s\n", "please enter key");
	scanf("%d", &key);
	return key;
}
