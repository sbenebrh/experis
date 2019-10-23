#include <string.h>  	/* strcat   */

#include "zlog4c.h" 	/*zlog_init */
#include "aggrMan.h"	/* AggrMan* */
#include "subAgg.h" 	/* SubAgr* 	*/
#include "QMan.h"		/*QMan_create*/

#define FILENAME 	"/home/samuel/work/IPCPROJECT2/files_part/cdro.txt"
#define FILENAME_QM "/home/samuel/work/IPCPROJECT2/files_part/cdro.txt"
#define PROTOCOLE 		'X'
#define PROTOCOLE_QM 	'V'
#define FILE_PROG 		"/files_part/files"
#define MAXPATH_SIZE 	512

static void parsefile(int * _capacity, int* _nthreads, int* _nlockers);
static int QMan_Create(SubAgr* _subagg, char* _filename, char _protocole);
static int Create_Reader();

int main()
{
	int capacity 			= 0;
	int numberOfLockers 	= 0;
	int numberOfThreads 	= 0;
	SubAgr* newSubAgr 		= NULL;
	AggrMan* aggr 			= NULL;

	zlog_init("logconfig");
	ZLOG(LOG_TRACE, "creation of system");

	parsefile(&capacity, &numberOfThreads, & numberOfLockers);
	if(Create_Reader() < 0)
	{
		/*return -1;*/
	}
	sleep(10);
	printf("end 10s\n");
	newSubAgr = SubAgr_Create(capacity,numberOfLockers);
	if(NULL == newSubAgr)
	{	
		ZLOG(LOG_DEBUG, "ERROR newSubAgr CREATION");
		return -1;
	}

	

	aggr = AggrMan_Create(numberOfThreads,newSubAgr, FILENAME, PROTOCOLE);
	if(aggr == NULL)
	{
		ZLOG(LOG_DEBUG, "ERROR Aggr CREATION");
		/*return -1;*/
	}

	if(QMan_Create(newSubAgr, FILENAME_QM, PROTOCOLE_QM) < 0)
	{
		ZLOG(LOG_DEBUG,"impossible to create QMan");
		/*return -1;*/
	}


	while(1);
	return 0;
	
}


/***************************************************************/
static void parsefile(int * _capacity, int* _nthreads, int* _nlockers)
{
	/*TODO parse config file*/
	*_capacity = 10;
	*_nthreads = 2;
	*_nlockers = 3;
}

static int QMan_Create(SubAgr* _subagg, char* _filename, char _protocole)
{
	pthread_t threadId = 0;

	ZLOG(LOG_TRACE, "create query manager");
	QMan* newQm = QManStruct_Create(_subagg, _filename, _protocole);
	if (NULL == newQm)
	{
		return -1;
	}
	if(pthread_create(&threadId, NULL, QMan_Run, newQm) != 0)
	{
		return -1;
	}
	/*TODO dont forget to destroy QmanStruct*/
	/*TODO join?*/
	pthread_join(threadId, NULL);
	return 1;
}

static int Create_Reader()
{
	int child = 0;
	char dirPath[MAXPATH_SIZE];
	char* argv[2];

	if(getcwd(dirPath, MAXPATH_SIZE) == NULL)
	{
		ZLOG(LOG_ERROR,"the pathname is too big" );
		return -1;
	}

	strcat(dirPath, FILE_PROG);
	printf("%s\n", dirPath);

	argv[0] = dirPath;
	argv[1] = NULL;
	child = fork();

	if(child == 0)
	{
		if(execve(argv[0],argv,NULL) == -1)
		{
			ZLOG(LOG_ERROR, "error execve");
		}
		
	}
	return 1;
}
