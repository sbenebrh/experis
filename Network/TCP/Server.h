#ifndef SERVER_H
#define SERVER_H

int InitServer(int mode,int port,const char * ip);
int ConnectServer(int);
void DataTransfer(int connfd);
void End(int connfd);
#endif
