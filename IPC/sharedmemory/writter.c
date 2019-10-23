#include <sys/ipc.h>	/*ipc*/
#include <sys/types.h>	/*portability*/
#include <stdlib.h>		/*malloc*/
#include <sys/sem.h>	/*semget*/
#include <sys/stat.h>	/*S_IRUSR*/
#include <sys/shm.h>	/*shmget*/
#include <stdio.h>		/*perror*/
#include <string.h>		/*strlen*/
#include <unistd.h>		/*getopt*/
#include <sys/msg.h>

#define WTOR_KEY 			'a'
#define RTOW_KEY 			'b'
#define SE_KEY 	 			'e'
#define WTR 				1
#define RTW 				0
#define OBJ_PERMS 			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP
#define BUFFER_SIZE			1024
#define SEMAPHORE_NUMBER	3
#define SEM_EMPTY			0
#define SEM_FULL			1
#define SEM_LOCK			2
#define ARGUMENT 			"n:f:wcdv"
#define FAIL 				-1
#define SUCCEES 			0
#define DEFAULT_FILENAME 	"sh.txt"
#define NUMBER_MESSAGE		2
#define WTOR_MESS			"i am the Writer and i send to Reader mess num: "
#define RTOW_MESS 			"i am the Reader and i send to Writer mess num: "
#define DOWN				-1
#define UP					1

union semun {
	int val;
	struct semid_ds * buf;
	unsigned short * array;
};

typedef struct SharedMemory
{
	int 	m_sem;
	int 	m_sh;
	void*   m_psh;
}SharedMemory;
struct shmseg
{
	int 	m_size;
	char 	m_buf[BUFFER_SIZE];
};

typedef struct SharedMflags
{
	unsigned int m_create:1;
	unsigned int m_verbose:1;
	unsigned int m_delete:1;
	char* 		 m_name;
	int 		 m_nmessage;
	unsigned int m_Iswriter:1;
}SharedMflags;

/*###############################STATIC DECLARATIONS#####################*/
static void 			run_Pingpong(int argc, char* argv[]);
static int 				initSemAvailable(int semId, int semNum);
static int 				initSemInUse(int semId, int semNum);
static SharedMemory* 	makeSharedMemory(const SharedMflags* _flags,int _side);
static SharedMemory* 	ShPack_Create(int sid,int shid,void* shmap);
static key_t 			getKey(const SharedMflags* _flags,int _side);
static int 				Create_Sem(const SharedMflags* _flags, int _key);
static int 				initSemaphore(const SharedMflags* _flags, int _sid);
static int 				get_flag(const SharedMflags* _flags , int _side);
static int 				attachSh(const SharedMflags* _flags , int _side, key_t key);
static SharedMflags * 	init(int argc, char* argv[]);
static void* 			Create_Sh(int _shid, const SharedMflags* _flags, int _side);
static void 			initPackage(SharedMemory* _packSh,int _sid,int _shid,void* _shmap);
static int 				semaphore_controler(const SharedMflags* _flags,int _side);
static int 				parse_arg(int argc, char* argv[], SharedMflags* _flags);
static void 			Flags_destroy(SharedMflags* _flags);
static int 				fillflag(int opt, char * optarg, struct SharedMflags* _flags);
static void 			initflag(SharedMflags* _flags);
static SharedMflags * 	Flags_create();
static void 			flow_message(SharedMemory* _wtor, SharedMemory* _rtow, SharedMflags* _flags);
static void 			send_Message(SharedMemory* _side,const SharedMflags* _flags);
static void				receive_Message(SharedMemory* _side);
static void 			deleteAll(SharedMemory* wtor, SharedMemory* rtow);
static void				writeToSharedMemory(SharedMemory* _side,const SharedMflags* _flags);
static void 			read_message(SharedMemory* _side);
/*###########################################################################*/
static void read_message(SharedMemory* _side)
{
	struct shmseg *shmp;
	shmp = _side -> m_psh;
	printf("%s\n",shmp->m_buf);
}
static void	writeToSharedMemory(SharedMemory* _side,const SharedMflags* _flags)
{
	static int i = 0;
	int size = 0;
	char sizebuf[sizeof(int)];
	char num[sizeof(int)];
	char message[sizeof(RTOW_MESS) +2 *sizeof(int)];

	size = sizeof(RTOW_MESS);
	sprintf(sizebuf,"%d",size);
/*TODO use memcpy in place of strcpy and strncpy*/
	strcpy(message,sizebuf);
	sprintf(num,"%d", i);

	if(_flags -> m_Iswriter)
	{
		strcat(message,WTOR_MESS);
	}
	else
	{
		strcat(message,RTOW_MESS);
	}

	strcat(message,num);
	strncpy((char*)_side -> m_psh,message,sizeof(RTOW_MESS) +2 * sizeof(int));
	i++;
}
static void send_Message(SharedMemory* _side,const SharedMflags* _flags)
{
	struct sembuf sop1, sop2,sop3 ;
	struct sembuf sops[SEMAPHORE_NUMBER] ; 
	
	sop1.sem_num = SEM_EMPTY;
	sop3.sem_num = SEM_FULL;
	sop2.sem_num = SEM_LOCK;
	sop1.sem_op = DOWN;
	sop2.sem_op = DOWN;
	sop3.sem_op = UP;
	sop1.sem_flg = 0;
	sop2.sem_flg = 0;
	sop3.sem_flg = 0;
	sops[0] = sop1;
	sops[1] = sop2;
	sops[2] = sop3;

	if(semop(_side -> m_sem, &sops[0], 1) < 0)
	{
		perror("getop");
		exit(1);
	}
	if(semop(_side -> m_sem, &sops[1], 1) < 0)
	{
		perror("getop");
		exit(1);
	}

	writeToSharedMemory(_side, _flags);

	sop2.sem_op = UP;
	sop3.sem_op = UP;
	sops[0] = sop3;
	sops[1] = sop2;
	if(semop(_side -> m_sem, &sops[0], 2) < 0)
	{
		perror("getop");
		exit(1);
	}
}
static void	receive_Message(SharedMemory* _side)
{
	struct sembuf sop1, sop2,sop3 ;
	struct sembuf sops[SEMAPHORE_NUMBER] ; 

	sop1.sem_num = SEM_EMPTY;
	sop3.sem_num = SEM_FULL;
	sop2.sem_num = SEM_LOCK;

	sop3.sem_op = DOWN;
	sop2.sem_op = DOWN;

	sops[0] = sop3;
	sops[1] = sop1;
	sops[2] = sop2;
	
	if(semop(_side -> m_sem, &sops[0], 1) < 0)
	{
		perror("getop");
		exit(1);
	}
	if(semop(_side -> m_sem, &sops[2], 1) < 0)
	{
		perror("getop");
		exit(1);
	}
	read_message(_side);

	sop2.sem_op = UP;
	sop1.sem_op = UP;
	sops[0] = sop1;
	sops[1] = sop2;
	if(semop(_side -> m_sem, &sops[0], 2) < 0)
	{
		perror("getop");
		exit(1);
	}
}
static void flow_message(SharedMemory* _wtor, SharedMemory* _rtow, SharedMflags* _flags)
{
	int i = _flags -> m_nmessage;
	while(1)
	{
		if(i == 0)
		{
			return ;
		}
		if(_flags -> m_Iswriter)
		{
			send_Message(_wtor, _flags);
			receive_Message(_rtow);
		}
		else
		{
			receive_Message(_wtor);
			send_Message(_rtow, _flags);
		}
		i--;
	}
}

static void deleteAll(SharedMemory* wtor, SharedMemory* rtow)
{
	printf("%s\n","deleteAll..." );
	shmdt(wtor -> m_psh);
	shmctl(wtor ->m_sh, IPC_RMID, NULL);
	shmdt(rtow -> m_psh);
	shmctl(rtow ->m_sh, IPC_RMID, NULL);
	semctl(wtor -> m_sem, SEMAPHORE_NUMBER, IPC_RMID, NULL);
	semctl(rtow -> m_sem, SEMAPHORE_NUMBER, IPC_RMID, NULL);

	free(wtor);
	free(rtow);
}

static void run_Pingpong(int argc, char* argv[])
{
	SharedMflags * flags = NULL;
	SharedMemory* wtor = NULL, *rtow = NULL;

	flags = init(argc, argv);

	wtor = makeSharedMemory(flags, WTR);
	rtow = makeSharedMemory(flags, RTW);

	flow_message(wtor,rtow, flags);
	if(flags -> m_delete)
	{
		deleteAll(wtor,rtow);
	}

	Flags_destroy(flags);
}

int main(int argc, char* argv[])
{
	run_Pingpong(argc,argv);
	return 0;
}

/***************************SEMOP******************************/
static int initSemAvailable(int semId, int semNum)
{
	union semun arg;
	arg.val = 1;
	return semctl(semId, semNum, SETVAL, arg);
}

static int initSemInUse(int semId, int semNum)
{
	union semun arg;
	arg.val = 0;
	return semctl(semId, semNum, SETVAL, arg);
}
static int Create_Sem(const SharedMflags* _flags, int _key)
{
	int flag = OBJ_PERMS;
	key_t key;

	if(_flags -> m_Iswriter && _flags -> m_create)
	{
		flag |= IPC_CREAT;
	}
	key = ftok(_flags -> m_name, _key);
	if(key < 0)
	{
		perror("ftok");
		exit(1);
	}
	return semget(key, SEMAPHORE_NUMBER, flag);
}

static int initSemaphore(const SharedMflags* _flags, int _sid)
{
	if(_flags -> m_create)
	{
		if(initSemAvailable(_sid,SEM_EMPTY) < 0 || 
							initSemAvailable(_sid,SEM_LOCK) < 0 ||
							initSemInUse(_sid,SEM_FULL) < 0)
		{
			return -1;
		}
	}
	return 0;
}

static int semaphore_controler(const SharedMflags* _flags,int _side)
{
	int sid = 0;

	if((sid = Create_Sem(_flags, _side)) < 0)
	{
		perror("Create_Sem");
		exit(1);
	}

	if(initSemaphore(_flags, sid) < 0)
	{
		perror("initSemaphore");
		exit(1);
	}
	return sid;
}
/***************************MAKESHAREDMEMORY*******************/

static SharedMemory* makeSharedMemory(const SharedMflags* _flags, int _side)
{
	key_t key = 0;
	int sid = 0;
	int shid = 0;
	void* shmap = NULL;
	SharedMemory* newShPackage = NULL;

	sid = semaphore_controler(_flags, _side);

	if((key = getKey(_flags, _side)) < 0)
	{
		perror("getKey");
		exit(1);
	}
	if((shid = attachSh(_flags, _side,key)) < 0)
	{
		perror("attachSh");
		exit(1);
	}

	if((shmap = Create_Sh( shid, _flags, _side)) == NULL )
	{
		perror("Create_Sh");
		exit(1);
	}
	newShPackage = ShPack_Create(sid, shid, shmap);
	return newShPackage;
}

static SharedMemory* ShPack_Create(int sid,int shid,void* shmap)
{
	SharedMemory* newShPackage = NULL;

	newShPackage = (SharedMemory*)malloc(sizeof(SharedMemory));
	if(NULL == newShPackage)
	{
		perror("allocation");
		exit(1);
	}
	initPackage(newShPackage, sid, shid, shmap);
	return newShPackage;
}

static key_t getKey(const SharedMflags* _flags,int _side)
{
	int protocole = 0;
	if(_side == WTR)
	{
		protocole = WTOR_KEY;
	}
	else
	{
		protocole = RTOW_KEY;
	}
	return ftok(_flags -> m_name, protocole);
}

static int get_flag(const SharedMflags* _flags , int _side)
{
	int flag  = 0;

	if(_flags -> m_create && _flags -> m_Iswriter)
	{
		flag |= IPC_CREAT;
	}
	flag |= OBJ_PERMS;

	return flag;
}

static int attachSh(const SharedMflags* _flags , int _side, key_t key)
{
	int flag  = 0;
	flag = get_flag(_flags, _side);
	return shmget(key, BUFFER_SIZE, flag);
}

static void* Create_Sh(int _shid,const SharedMflags* _flags, int _side)
{
	int flag = 0;
	if((_flags -> m_Iswriter && _side == RTW) || (_flags -> m_Iswriter == 0 && _side == WTR))
	{
		flag = SHM_RDONLY;
	}
	return shmat(_shid, NULL, flag);
}

static void initPackage(SharedMemory* _packSh,int _sid,int _shid,void* _shmap)
{
	_packSh -> m_sem = _sid  ;
	_packSh -> m_sh  = _shid ;
	_packSh -> m_psh = _shmap;
}


/***************************FLAGS******************************/

static SharedMflags * init(int argc, char* argv[])
{
	SharedMflags * flags = Flags_create();
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

static int parse_arg(int argc, char* argv[], SharedMflags* _flags)
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

static void Flags_destroy(SharedMflags* _flags)
{
	free(_flags->m_name);
	free(_flags);
}

static int fillflag(int opt, char * optarg, struct SharedMflags* _flags)
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

		case 'f':
			lenth_path_name = strlen(optarg);
			_flags -> m_name = (char*) malloc(lenth_path_name * sizeof(char));
			strcpy(_flags -> m_name, optarg);
			break;

		case 'n':
			_flags -> m_nmessage = atoi(optarg);
			break;

		case 'w':
			_flags -> m_Iswriter = 1;
			break;

		default:
			result = FAIL;
			break;
	}	
	return result;
}

static void initflag(SharedMflags* _flags)
{
	int lenght = 0;
	_flags -> m_create   = 0;
	_flags -> m_verbose  = 0;
	_flags -> m_delete   = 0;
	_flags -> m_Iswriter = 0;
	_flags -> m_nmessage = 0;

	lenght = sizeof(DEFAULT_FILENAME);
	_flags -> m_name = malloc(lenght * sizeof(char));
	strcpy(_flags -> m_name, DEFAULT_FILENAME);
}

static SharedMflags * Flags_create()
{
	return (SharedMflags*) malloc (sizeof(SharedMflags));
}
/*************************************************************************/