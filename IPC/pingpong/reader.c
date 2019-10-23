#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>
#include <sys/ipc.h>


#define ARGUMENT "e:f:s:v"
#define SUCCEES 0
#define FAIL -1
#define PERMS S_IRUSR | S_IWUSR
#define PROTOCOL 'w'
#define MESSAGE_OK "OK"
#define MAXBYTES 64
#define END_MESSAGE "****FIN****"
#define ACK_MESSAGE "OK"
#define END_TYPE	2
#define WTOR		1L
#define RTOW		3L
#define MILTOUFACT	1000
#define DEFAULT_MSQ "./a.txt"
#define ALLRECEIVE	-END_TYPE
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


/*##################STATIC########################*/
static int 		queue_Create(key_t _key);
static FlagMq* 	Flags_create();
static void 	Flags_destroy(FlagMq* _flags);
static int 		fillflag(int opt, char * optarg, struct FlagMq* _flags);
static int 		parse_arg(int argc, char* argv[], struct FlagMq* _flags);
static int 		get_key(FlagMq* _flags);
static void 	receiver_flow(int msqid, FlagMq* _flags);
static FlagMq* 	init(int * msqid, int argc, char* argv[]);
static int 		run_message_reader(int argc, char* argv[]);
static void 	initflag(FlagMq* _flags);
/*#####################################################*/

int main(int argc, char* argv[])
{
	return run_message_reader(argc,argv);
}
/**************************************************************/



static int queue_Create(key_t _key)
{
	int msqid = 0;
	msqid = msgget(_key, 0|PERMS);/*TODO check flags*/
	if(msqid < 0)
	{
		perror("msgget");
		exit(1);
	}
	return msqid;
}
static FlagMq * Flags_create()
{
	return (FlagMq*) malloc (sizeof(FlagMq));
}

static void Flags_destroy(FlagMq* _flags)
{
	free(_flags);
}
static int fillflag(int opt, char * optarg, struct FlagMq* _flags)
{
	int result = SUCCEES;
	int lenth_path_name = 0;
	
	switch(opt)
	{
		case 'v':
			_flags -> m_verbose = 1;
			break;

		case 'e':
			_flags -> m_eof = 1;
			break;

		case 's': 
			_flags -> m_sleep = atoi(optarg);
			break;

		case 'f':
		free(_flags -> m_name);
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

static void receiver_flow(int msqid, FlagMq* _flags)
{
	char msg[104] = {0};
	int msgLen;
	struct  msgbuf *pmsg;
	pmsg = (struct msgbuf*)msg;
	
	while(1)
	{
		if(msgrcv(msqid, pmsg, 104, ALLRECEIVE, 0)<0)
		{
			perror("msgrcv");
			exit(1);
		}
		if(strcmp(END_MESSAGE, pmsg -> mtext) == 0 && (_flags -> m_eof == 0))
		{
			return;
		}
		if(pmsg -> mtype == END_TYPE)
		{
			return;
		}

		printf("%s\n",pmsg -> mtext );


		if(_flags -> m_sleep)
		{
			usleep(_flags -> m_sleep * MILTOUFACT);
		}

		pmsg -> mtype = RTOW;
		strcpy(pmsg -> mtext, ACK_MESSAGE);
		msgsnd(msqid, pmsg, sizeof(ACK_MESSAGE), IPC_NOWAIT);
	}
}
static FlagMq * init(int * msqid, int argc, char* argv[])
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
		perror("key");
		Flags_destroy(flags);
		return NULL;
	}
	*msqid = queue_Create(key);
	if(*msqid < 0)
	{
		perror("msqid");
		Flags_destroy(flags);
		return NULL;
	}
	return flags;
}
static int run_message_reader(int argc, char* argv[])
{
	int msqid = 0;
	FlagMq * flags = NULL;

	flags = init(&msqid,argc, argv);
	if(flags == NULL)
	{
		perror("flags");
		exit(1);
	}
	printf("%d\n",msqid );
	receiver_flow(msqid,flags);
	return SUCCEES;
}
static void initflag(FlagMq* _flags)
{
	int lenght = 0;
	_flags -> m_verbose= 0;
	_flags -> m_eof= 0;
	lenght = sizeof(DEFAULT_MSQ);
	_flags -> m_name = malloc(lenght * sizeof(char));
	strcpy(_flags -> m_name, "./a.txt");
	_flags -> m_sleep = 0;
}
