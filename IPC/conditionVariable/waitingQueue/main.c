#include <stdlib.h>
#include <unistd.h>

#include "wQueue.h"
#include "producer.h"
#include "consumers.h"

#define ARGUMENT 			"p:c:vq:"
#define SUCCEES				0
#define FAIL				-1
typedef struct Flag
{
	int m_producers;
	int m_consumers;
	int m_queueSize;
	unsigned int m_verbose;
}Flag;


static Flag * 	Flags_create();
static Flag * 	init(int argc, char* argv[]);
static int 		parse_arg(int argc, char* argv[], Flag* _flags);
static int 		fillflag(int opt, char * optarg, struct Flag* _flags);
static void 	initflag(Flag* _flags);
static Flag * 	Flags_create();
static void 	Flags_destroy(Flag* _flags);

static Flag * init(int argc, char* argv[])
{
	Flag * flags = Flags_create();
	if(NULL == flags)
	{
		perror("allocation");
		exit(1);
	}

	if(parse_arg(argc, argv,flags) != SUCCEES)
	{
		perror("parse_arg");
		Flags_destroy(flags);
		exit(1);
	}
	
	return flags;
}
static int parse_arg(int argc, char* argv[], Flag* _flags)
{
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
static int fillflag(int opt, char * optarg, struct Flag* _flags)
{
	int result = SUCCEES;
	int lenth_path_name = 0;
	
	switch(opt)
	{
		case 'c':
			_flags -> m_consumers = atoi(optarg);
			break;

		case 'v':
			_flags -> m_verbose = 1;
			break;

		case 'p':
			_flags -> m_producers = atoi(optarg);
			break;

		case 'q':
			_flags -> m_queueSize = atoi(optarg);
			break;

		default:
			result = FAIL;
			break;
	}	
	return result;
}

static void initflag(Flag* _flags)
{
	int lenght = 0;
	_flags -> m_consumers  = 0;
	_flags -> m_verbose    = 0;
	_flags -> m_producers  = 0;
}

static Flag * Flags_create()
{
	return (Flag*) malloc (sizeof(Flag));
}

static void Flags_destroy(Flag* _flags)
{
	free(_flags);
}

int main(int argc , char* argv[])
{
	/*parse();
	Create_Wqueue(2);
	create_producers(1);
	create_consumers(1);
	join_producers();
	join_consumers();
	...;*/
	Producers* newPreoducer = NULL;
	Consumers* newConsumer = NULL;
	Flag* flags =NULL;
	WQueue* wqueue = NULL;
	flags = init(argc,argv);
	wqueue = WQueue_Create(flags -> m_queueSize);
	if(NULL == wqueue)
	{
		exit(1);
	}
	
	newPreoducer = create_producers(flags -> m_producers, wqueue);
	sleep(0);
	if(NULL == newPreoducer)
	{
		exit(1);
	}
	newConsumer = Create_Consumers(flags -> m_consumers,wqueue);
	join_producers(newPreoducer);
	printf("start kill\n");
	kill_Consumers(newConsumer,wqueue);
	printf("join\n");
	join_Consumers(newConsumer,wqueue);
	
	printf(" END join\n");
	Flags_destroy(flags);
	
	Destroy_producers(&newPreoducer);
	Destroy_Consumers(&newConsumer);
	WQueue_Destroy(&wqueue,NULL);
	return 0;
}
