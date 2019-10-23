#include "Client.h"
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <time.h>

#include "tcp.h"
#define MAX 1024
#define CLIENTS_NUM 10

void FillServerInfo(struct sockaddr_in* servaddr,int mode,int port,const char * ip)
{
	memset(servaddr,0,sizeof(*servaddr));
    servaddr->sin_family=mode; 
    servaddr->sin_addr.s_addr=inet_addr(ip); 
    servaddr->sin_port=htons(port);	
}
int InitClient(int mode,int port,const char * ip)
{
    int sfd ;
    struct sockaddr_in addr;
    if(CreateSocket(mode, port,&addr, ip, &sfd) != TCP_OK)
    {
        perror("CreateSocket");
        abort();
    }
    return sfd;
}
static int ConnectClient(int sfd, struct sockaddr_in* servaddr)
{
    
    int length = sizeof(*servaddr);
    return Connect(sfd, servaddr, length);
}

static void DataTransferClient(int connfd, int i)
{
    char buff[MAX]; 
    int n; 
    int length = 0;
    memset(buff, 0, MAX);  
    sprintf(buff,"client#%d",i);
    
    
    length = strlen(buff) + 1; 

    write(connfd, buff, length);
    printf("I sent %s\n",buff); 
    memset(buff, 0, MAX);  

    
    read(connfd, buff, MAX); 
    printf("From Server: %s\n\n", buff); 
        
}

void EndClient(int connfd)
{
    closeSocket(connfd);
}
void Run(struct sockaddr_in* servaddr,int mode,int port,const char * ip )
{
    int sockfd,i;
	int toConnect,j=0;
	int clientsArr[CLIENTS_NUM]={0};
    int flag = 1;
    int index = 0;
	time_t t ;

	for(i=0; i<CLIENTS_NUM/2; i++)
	{	
	    clientsArr[i]=InitClient(mode, port, ip);
		ConnectClient(clientsArr[i],servaddr);
		printf("client# %d connected\n",i);
		
	}

	while(1)
	{
		srand((unsigned) time(&t));
		
		index=rand()%CLIENTS_NUM; 
        printf("client#%d action\n",index);

		/* client is connected, talk with server */
		if(clientsArr[index] != 0 && flag == 1)
		{			
			DataTransferClient(clientsArr[index],index);	
			flag=0;
            continue;
            
		}

		/* client is connected, disconnect it */
		else if(clientsArr[index] != 0 && flag == 0)
		{			
			EndClient(clientsArr[index]);
			clientsArr[index]=0;
			flag=1;
			printf("client#%d disconnected\n",index);
            continue;
            
		}

		/* client disconnected, connect it */
		if(clientsArr[index] == 0)
		{
		    clientsArr[index]=InitClient(mode, port, ip);
            if(ConnectClient(clientsArr[index],servaddr)!= TCP_OK)
            {
                printf("client#%d not succeed to connected\n",index);
                clientsArr[index] = 0;
                continue;
            }
			printf("client#%d connected\n",index);
            continue;
            
		}
		
	}
}

