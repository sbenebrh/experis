#include "Channel.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* RunSender(void* context)
{
    char mess[64] = "Sender ";
    if(Send_Message(*(QID*)context, mess) != CHANNEL_OK)
    {
        printf("Error send\n");
        return NULL;
    }
    return NULL;

}

static void* RunReceiver(void* context)
{
    char message[64];
    if(Receive_Message(*(QID*)context, message) != CHANNEL_OK)
    {
        printf("Error Receive1\n");
        return NULL;
    }
    printf("%s\n", message);
    if(Receive_Message(*(QID*)context, message) != CHANNEL_OK)
    {
        printf("Error Receive2\n");
        return NULL;
    }
    printf("%s\n", message);
}
static void flow()
{
    QID id ;
    pthread_t sender1;
    pthread_t sender2;
    pthread_t receiver;
    Create_Channel(&id, "./a.txt");
    if(pthread_create(&sender1, NULL,RunSender, (void*)&id)!= 0)
    {
        perror("create thread1");
        exit(-1);
    }
    if(pthread_create(&sender2, NULL,RunSender, (void*)&id)!= 0)
    {
        perror("create thread1");
        exit(-1);
    }
     if(pthread_create(&receiver, NULL,RunReceiver, (void*)&id)!= 0)
    {
        perror("create thread1");
        exit(-1);
    }
    pthread_join(sender1, NULL);
    pthread_join(sender2, NULL);
    pthread_join(receiver, NULL);
}


int main()
{

    flow();
    return 0;
}