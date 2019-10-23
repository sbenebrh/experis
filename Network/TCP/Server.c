#include "Server.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <strings.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <errno.h>

#include "tcp.h"
#include "list.h"
#include "list_itr.h"

#define MAX 1024

int InitServer(int mode,int port,const char * ip)
{
    int sfd ;
    struct sockaddr_in addr;
    if(CreateSocket(mode, port,&addr, ip, &sfd) != TCP_OK)
    {
        perror("CreateSocket");
        abort();
    }

    if(BindSocket(sfd, &addr) != TCP_OK)
    {
        perror("BindSocket");
        abort();
    }
    if(ListenSocket(sfd) != TCP_OK)
    {
        perror("ListenSocket");
        abort();
    }
    return sfd;
}

int ConnectServer(int sfd)
{
    struct sockaddr_in addr;
    int result;
    socklen_t length = sizeof(addr);
    if(AcceptData(sfd, (struct sockaddr*) &addr, &length,&result)!= TCP_OK)
    {
        perror("AcceptData");
        abort();
    }
    return result;
}


static void checkNewClient(int sfd, List* list, int * clientsCount)
{
    int result ;
    int * newClient;
    struct sockaddr_in addr;
    socklen_t length = sizeof(addr);
    if(AcceptData(sfd, (struct sockaddr*) &addr, &length,&result) == TCP_OK)
    {
        newClient=(int*) malloc(sizeof(int));
		if(!newClient) 
        {
            abort();
        }
		*newClient = result;
        printf("%d\n",*newClient);
		ListItr_InsertBefore(ListItr_Begin(list),newClient);
		(*clientsCount)++;
    }

}
void DataTransfer(int connfd)
{
    char buff[MAX]; 
    int n; 
    struct sockaddr_in addr;
    int result;
    List * listClient;
    ListItr it;
    ListItr end;
    ListItr tmp;
    int i ;
    int size;
    int item;
    int res = 0;
    int count = 0;
    
    socklen_t length = sizeof(addr);
    listClient = List_Create();
    if(listClient == NULL)
    {
        abort();
    }

    bzero(buff, MAX); 
    
 	
	

    while(1)
    {
        checkNewClient(connfd, listClient, &count);
        it=ListItr_Begin(listClient);
        end=ListItr_End(listClient); 
        
        for( i = 0; it != end;++i)
        {
            bzero(buff, MAX); 

            res = readFrom(*(int*)ListItr_Get(it), buff, sizeof(buff)); 
            if(res == 0)
		    {
                close(*(int*)ListItr_Get(it));
                tmp=it;
                it=ListItr_Next(it);
                ListItr_Remove(tmp);
                continue;
		    }

            if(res < 0)
            {
                if(errno == EWOULDBLOCK || errno == EAGAIN)
                {	
                    it = ListItr_Next(it);
                    continue;
                }
                else
                {
                    printf("read failed\n");
                    exit(1);
                }
            }
            printf("From client: %s\t To client : ", buff); 
            bzero(buff, MAX); 
            n = 0; 
            strcpy(buff, "ack");

            write(*(int*)ListItr_Get(it), (const char*)buff, strlen(buff) + 1);
            printf("sent to client: %s\n\n", buff); 

            it=ListItr_Next(it);
        }
        
 
        
    }
      
    
}

void End(int connfd)
{
    closeSocket(connfd);
}
 