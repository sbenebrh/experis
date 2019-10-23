#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>

#define SUCCEES 0
#define FAIL -1
#define PERMS S_IRUSR | S_IWUSR
#define MESSAGE "hello mess number:" 
#define PROTOCOL 'w'
#define ARGUMENT "e:f:n:s:cdv"
#define END_MESSAGE "****FIN****"
#define MAXBYTES 108
#define DEFAULT_NMESSAGE	5
#define MILTOUFACT	1000
#define END_TYPE	2L
#define WTOR		1L
#define RTOW		3L
#define DEFAULT_MSQ "./a.txt"

typedef struct FlagMq
{
	unsigned int m_create:1;
	unsigned int m_verbose:1;
	unsigned int m_eof:1;
	unsigned int m_delete:1;
	char* 		 m_name;
	unsigned int m_nOfMess;
	unsigned int m_sleep;
}FlagMq;

struct msgbuf 
{
    long mtype;
    char mtext[1];
};
/*#############################################*/
static int 		queue_Create(key_t _key, FlagMq* _flags);
static FlagMq* 	Flags_create();
static void 	Flags_destroy(FlagMq* _flags);
static int 		fillflag(int opt, char * optarg, struct FlagMq* _flags);
static int 		parse_arg(int argc, char* argv[], struct FlagMq* _flags);
static int 		get_key(FlagMq* _flags);
static void 	Send_message(int msqid);
static int 		read_message(int msqid);
static int 		send_endMess(FlagMq* flags, int msqid);
static int 		run_message_writter(int argc, char* argv[]);
static FlagMq* 	init(int argc, char* argv[],int* msqid);
static void 	initflag(FlagMq* _flags);
/*############################################*/
int main(int argc, char* argv[])
{
	int result = run_message_writter(argc, argv);
	return result;
}

/*************************************************/
static int queue_Create(key_t _key, FlagMq* _flags)
{
	int flag = PERMS;
	if(_flags -> m_create == 1)
	{
		flag |= IPC_CREAT; 
	}
	return msgget(_key, flag);
}

static FlagMq * Flags_create()
{
	return (FlagMq*) malloc (sizeof(FlagMq));
}

static void Flags_destroy(FlagMq* _flags)
{
	free(_flags->m_name);
	free(_flags);
}

static int fillflag(int opt, char * optarg, struct FlagMq* _flags)
{
	int result = SUCCEES;
	int lenth_path_name = 0;
	
	switch(opt)
	{
		case 'c':
			_flags -> m_create = 1;
			break;

		case 'v':
			_flags -> m_verbose = 1;
			break;

		case 'd':
			_flags -> m_delete = 1;
			break;

		case 'e':
			_flags -> m_eof = 1;
			break;

		case 'n':
			_flags -> m_nOfMess = atoi(optarg);
			break;

		case 's': 
			_flags -> m_sleep = atoi(optarg);
			break;

		case 'f':
			lenth_path_name = strlen(optarg);
			_flags -> m_name = (char*) malloc(lenth_path_name * sizeof(char));
			strcpy(_flags -> m_name, optarg);
			break;

		default:
			result = FAIL;
			break;
	}	
	return result;
}


static int parse_arg(int argc, char* argv[], struct FlagMq* _flags)
{
	int lenth_path_name = 0;
	int opt = 0;
	initflag(_flags);
	while((opt = getopt(argc, argv, ARGUMENT)) != -1)
	{
		if(fillflag(opt, optarg, _flags) == FAIL)
		{
			return FAIL;
		}
	}
	return SUCCEES;
} 
static int get_key(FlagMq* _flags)
{
	
	return ftok(_flags -> m_name, PROTOCOL);
}

static void Send_message(int msqid)
{
	char msg[MAXBYTES];
	char num[sizeof(int)];
	static int i = 0;
	struct  msgbuf *pmsg;
	pmsg = (struct msgbuf*)msg;
	pmsg -> mtype = WTOR;

	strcpy(pmsg -> mtext, MESSAGE);
	sprintf(num, "%d", i);
	strcat(pmsg -> mtext,num);

	if(msgsnd(msqid, pmsg,MAXBYTES, IPC_NOWAIT) < 0)
	{
		perror("msgsnd w");
		exit(1);
	}
	i++;
}

static int read_message(int msqid)
{
	int msgLen;
	char msg[MAXBYTES] = {0};
	struct  msgbuf *pmsg;
	pmsg = (struct msgbuf*)msg;
	pmsg -> mtype = RTOW;
	msgLen = msgrcv(msqid, pmsg, MAXBYTES, pmsg -> mtype, IPC_NOWAIT);
	if (msgLen == -1)
	{
		perror("msgrcv");
		return FAIL;
	}
	printf("%s\n",pmsg -> mtext );
	return SUCCEES;
}
static int send_endMess(FlagMq* flags, int msqid)
{
	char msg[MAXBYTES];
	int msgLen;
	struct  msgbuf *pmsg;
	pmsg = (struct msgbuf*)msg;
	pmsg -> mtype = END_TYPE;
	if(flags -> m_eof)
	{
		pmsg -> mtype = END_TYPE;
	}
	strcpy(pmsg -> mtext, END_MESSAGE);
	msgLen = msgsnd(msqid, pmsg, MAXBYTES, IPC_NOWAIT);
	if(msgLen < 0)
	{	perror("msgsnd");
		return FAIL;
	}

}

static FlagMq * init(int argc, char* argv[],int* msqid)
{
	key_t key = 0;
	
	FlagMq * flags = Flags_create();
	if(NULL == flags)
	{
		return NULL;
	}

	if(parse_arg(argc, argv,flags) != SUCCEES)
	{
		Flags_destroy(flags);
		return NULL;
	}
	
	if((key = get_key(flags)) < 0)
	{
		printf("%s\n","creation mss" );
		Flags_destroy(flags);
		return NULL;
	}
	
	*msqid = queue_Create(key, flags);
	if(*msqid < 0)
	{
		perror("msqid");
		Flags_destroy(flags);
		exit(1);
	}

	return flags;
}

static int writter_flow(int msqid, FlagMq* flags)
{
		while(flags -> m_nOfMess)
		{
			Send_message(msqid);
			if(flags -> m_sleep)
			{
				usleep(flags -> m_sleep * MILTOUFACT);
			}
			if(read_message(msqid)== FAIL)
			{
				Flags_destroy(flags);
				if(flags -> m_verbose)
				{
					perror("read_message");
				}
				return FAIL;	
			}
			flags -> m_nOfMess --;
		}
		
		if(send_endMess(flags,msqid) == FAIL)
		{
			Flags_destroy(flags);
			return FAIL;
		}
	return SUCCEES;
}
static int run_message_writter(int argc, char* argv[])
{
	key_t key;
	int msqid;

	
	FlagMq * flags = init(argc, argv, &msqid);
	if(NULL == flags)
	{
		return FAIL;
	}
	printf("%d\n",msqid );
	if(writter_flow(msqid, flags) == FAIL)
	{
		Flags_destroy(flags);
		return FAIL;
	}

	if(flags -> m_delete == 1)
	{
		msgctl(msqid,IPC_RMID,NULL);
		return SUCCEES;
	}
	Flags_destroy(flags);

	return SUCCEES;
}

static void initflag(FlagMq* _flags)
{
	int lenght = 0;
	_flags -> m_create = 0;
	_flags -> m_verbose= 0;
	_flags -> m_eof= 0;
	_flags -> m_delete= 0;
	lenght = sizeof(DEFAULT_MSQ);
	_flags -> m_name = malloc(lenght * sizeof(char));
	strcpy(_flags -> m_name, DEFAULT_MSQ);
	_flags -> m_nOfMess = 0;
	_flags -> m_sleep = 0;
}
