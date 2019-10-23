#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 

void Run(struct sockaddr_in* servaddr,int mode,int port,const char * ip );
void FillServerInfo(struct sockaddr_in* servaddr,int mode,int port,const char * ip);
/*int InitClient(int mode,int port,const char * ip);
int ConnectClient(int);
void DataTransferClient(int connfd);
void EndClient(int connfd);*/

#endif