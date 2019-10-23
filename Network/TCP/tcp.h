#ifndef TCP_H
#define TCP_H

#include <sys/types.h> 
#include<unistd.h>
typedef __socklen_t socklen_t;

typedef enum Tcp_Result
{
    TCP_OK,
    SOCKET_ERROR, 
    INVALID_ARGUMENT_ERROR,
    SETSOCKOPT_ERROR,
    BIND_ERROR,
    LISTEN_ERROR,
    ACCEPT_ERROR,
    CONNECT_ERROR

} Tcp_Result;

#define BACKLOG     5

Tcp_Result CreateSocket(int mode, int port, void* addr, const char * ip, int *sfd);
int BindSocket(int sfd, void* addr);
int ListenSocket(int sfd);

int AcceptData(int sfd, void* addr, socklen_t* length,int* inner);
int Connect(int sfd, void* addr, int length);

ssize_t readFrom(int sfd, char*  buf, int length);
ssize_t writeTo(int sfd, char* buf, int length);

void closeSocket(int sfd);




#endif
