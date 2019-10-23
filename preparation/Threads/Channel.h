#ifndef CHANNEL_H
#define CHANNEL_H

typedef enum Result_Channel
{
    CHANNEL_OK,
    INVALID_FILE_ERROR,
    CREATE_CHANNEL_ERROR,
    SEND_MESSAGE_ERROR,
    FAIL
}Result_Channel;

typedef int QID;
Result_Channel Create_Channel(QID* Qid, char* file);
Result_Channel Send_Message(QID qid, char * msgout);
Result_Channel Receive_Message(QID qid, char* msgin);
void Delete_Channel(QID qid);


#endif