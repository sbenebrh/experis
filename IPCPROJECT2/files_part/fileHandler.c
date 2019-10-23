#include <stdio.h>  	/* perror	*/
#include <sys/types.h> 	/* ftok		*/
#include <sys/ipc.h> 	/* ftok		*/
#include <string.h> 	/* strcpy	*/
#include <sys/msg.h> 	/* msgget	*/
#include <sys/stat.h> 	/* S_IRUSR	*/
#include <stdlib.h>	 	/* exit 	*/

#include "cdr.h"
#include "zlog4c.h"

#define FILE_NAME		"./cdro.txt" /*TODO receive file name from file monitor*/
#define PROTOCOLE 		'X'	/*TODO receive file name from file monitor*/
#define PERMS 			IPC_CREAT|S_IRUSR | S_IWUSR
#define READ 			"r"
#define BUFFER_SIZE_OP 	64
#define BUFF 			16
#define RTOAG			1
#define MAX_BUFFER		1024

struct msgbuf {
    long mtype;       /* message type, must be > 0 */
    char mtext[1];    /* message data */
};
/*########################################################*/
static int 		createChannel(char * _filename, char _protocole);
static int 		parseline(FILE* _file, long* _position,CDR* _cdr);
static void 	initCdr(CDR* _cdr,size_t imsi,size_t msisdn,size_t imei, char *OpName,char * callType, size_t duration,size_t download,size_t upload,size_t PartMsisnd,char *PartOp);
static void 	sendCdr(int _id,CDR* cdr);
static CallType parseCallType(char* callType);
static size_t 	getNumberline(FILE* _file,long* _position);
/*###########################################################*/
int main(int argc , char* argv[])
{
	int id 			= 0;
	int res 		= 0;
	long position 	= 0;
	int numberline 	= 0;
	FILE * file 	= NULL;
	CDR cdr ;
	zlog_init("logconfig");
	printf("hello\n");
	id = createChannel(FILE_NAME, PROTOCOLE);
	
	file = fopen(argv[1],READ);
	if(NULL == file)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO open file");
		perror("fopen");
		return -1;

	}
	
	numberline = getNumberline(file,&position);
	
	while(numberline)
	{
		res = parseline(file,&position,&cdr);
		if(res == -1)
		{
			ZLOG(LOG_TRACE, "end of file");
			break;
		}
		sendCdr(id, &cdr);
		numberline--;
	}
	fclose(file);
}


/*########################################################################*/
static int createChannel(char * _filename, char _protocole)
{
	key_t key = 0;
	int msqid = 0;
	
	key = ftok(_filename, _protocole);
	ZLOG(LOG_TRACE, "CREATE CHANNEL READER");
	if(key == -1)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO GET KEY");
		perror("ftok");
	}

	msqid = msgget(key, PERMS);
	if(msqid < 0)
	{
		perror("msgget");
		exit(1);
	}
	return msqid;
}

static int parseline(FILE* _file, long* _position,CDR* _cdr)
{
	size_t imsi 	 	= 0;
	size_t msisdn 		= 0;
	size_t imei         = 0;
	size_t temp			= 0;
	size_t duration 	= 0;
	size_t download 	= 0;
	size_t upload 		= 0;
	size_t PartMsisnd  	= 0;
	char OpName[BUFFER_SIZE_OP];
	char callType[BUFF];
	char tempstr[BUFF];
	char PartOp[BUFFER_SIZE_OP];

	fseek(_file, *_position,SEEK_SET);
	
	fscanf(_file,
			"%ld|%ld|%ld|%s|%ld|%s|%s|%s|%ld|%ld|%ld|%ld|%s",
			&imsi,&msisdn,&imei,OpName,&temp,callType,tempstr,
			tempstr,&duration,&download,&upload,&PartMsisnd,PartOp);
			
	initCdr(_cdr, imsi,msisdn,imei,OpName,callType,duration,download,upload,PartMsisnd,PartOp);
	*_position = ftell(_file);
	if(ftell(_file) != feof(_file))
	{
		return 0;
	}
	 return -1;
}

static void initCdr(CDR* _cdr,size_t imsi,size_t msisdn,size_t imei, char *OpName,char * callType, size_t duration,size_t download,size_t upload,size_t PartMsisnd,char *PartOp)
{

	_cdr ->m_IMSI 			= imsi;
	_cdr ->m_MSISDN			= msisdn;
	_cdr ->m_IMEI 			= imei;
	_cdr ->m_duration		= duration;
	_cdr ->m_download		= download;
	_cdr ->m_upload			= upload;
	_cdr -> m_partyMSISDN 	= PartMsisnd;

	strcpy(_cdr -> m_OpName,OpName);
	strcpy(_cdr -> m_partyOperator, PartOp);
	_cdr -> m_callType =  parseCallType(callType);
}

static CallType  parseCallType(char* callType)
{
	CallType type;
	switch(callType[0])
	{
		case 'M':
			if(callType[1] == 'O')
			{
				type = CDR_MOC;
			}
			else
				type = CDR_MTC;
			break;

		case 'G':
			type = CDR_GPRS;
			break;

		case 'S':
			if(callType[5] == 'O')
				type = CDR_SMS_MO;
			else
				type = CDR_SMS_MT;
			break;
	}
	return type;
}

static void sendCdr(int _id,CDR* cdr)
{
	ZLOG(LOG_TRACE,"SEND CDR");
	struct  msgbuf *pmsg;
	char buff[MAX_BUFFER];
	pmsg = (struct msgbuf*)buff;
	pmsg -> mtype = RTOAG;
	memcpy(pmsg -> mtext,cdr,sizeof(CDR));
	ZLOG(LOG_DEBUG, "send message to channel");
	if(msgsnd(_id,pmsg,sizeof(CDR),IPC_NOWAIT) < 0)
	{
		ZLOG(LOG_ERROR, "IMPOSSIBLE TO SEND TO MSQ");
		perror("msgsnd w ");
	}
}


static size_t 	getNumberline(FILE* _file,long* _position)
{
	int numberOfLine = 0;
	fscanf(_file, "%d",&numberOfLine);
	*_position = ftell(_file);
	
	return numberOfLine;
}
