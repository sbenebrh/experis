#include "Channel.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <stdio.h>

#define WTOR		1L
#define MAXBYTES 128
#define PERMS S_IRUSR | S_IWUSR | IPC_CREAT

static key_t Get_Key(char* file);
struct msgbuf 
{
    long mtype;
    char mtext[1];
};

Result_Channel Create_Channel(QID* Qid, char* file)
{
    key_t key = 0;
    
    key = Get_Key(file);
    if(key < 1)
    {
        return INVALID_FILE_ERROR;
    }
    *Qid = msgget(key, PERMS);
    if(*Qid == -1)
    {
        return CREATE_CHANNEL_ERROR;
    }
    return CHANNEL_OK;
}

Result_Channel Send_Message(QID qid, char * msgout)
{
    char * mess = (char*)malloc(strlen(msgout) + 1);
    strcpy(mess, msgout);
    printf("%s\n", mess);
    char msg[64];
	char num[sizeof(int)];
	static int i = 0;
	struct  msgbuf *pmsg;
	pmsg = (struct msgbuf*)msg;
	pmsg -> mtype = 1L;

	strcpy(pmsg -> mtext, mess);
	sprintf(num, "%d", ++i);
	strcat(pmsg -> mtext,num);
	if(msgsnd(qid, pmsg,64, IPC_NOWAIT) < 0)
	{
		perror("msgsnd w");
        free(mess);
		return SEND_MESSAGE_ERROR;
	}
    free(mess);
    return CHANNEL_OK;
	
}

Result_Channel Receive_Message(QID qid, char* msgin)
{
    int msgLen;
	char msg[MAXBYTES] = {0};
	struct  msgbuf *pmsg;
	pmsg = (struct msgbuf*)msg;
	pmsg -> mtype =1L;
	msgLen = msgrcv(qid, pmsg, 64,0, 0);
	if (msgLen == -1)
	{
		perror("msgrcv");
		return FAIL;
	}

	strcpy(msgin,pmsg ->mtext );
    
	return CHANNEL_OK; 
}


/**************************************************/


static key_t Get_Key(char* file)
{
    return ftok(file, 'a');
}