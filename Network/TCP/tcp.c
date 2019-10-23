#include "tcp.h"

#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#include <fcntl.h>

#define FAIL -1

Tcp_Result CreateSocket(int mode, int port, void* addr, const char * ip, int * sfd)
{
    if(addr == NULL || ip == NULL || sfd == NULL)
    {
        return INVALID_ARGUMENT_ERROR;
    }
     *sfd = socket(AF_INET, SOCK_STREAM, 0);
    
    if(*sfd < 0)
    {
        return SOCKET_ERROR;
    }
    memset((struct sockaddr_in*)addr, 0, sizeof(addr));
    ((struct sockaddr_in*)addr)-> sin_family = AF_INET; 
    ((struct sockaddr_in*)addr) -> sin_addr.s_addr = inet_addr(ip); 
    ((struct sockaddr_in*)addr) -> sin_port = htons(port); 

    return TCP_OK;
}
int BindSocket(int sfd, void* addr)
{
    int optval = 1;
    if(addr == NULL)
    {
        return INVALID_ARGUMENT_ERROR;
    }

    if(setsockopt(sfd, SOL_SOCKET, SO_REUSEADDR, 
                    &optval, sizeof(optval))< 0)
    {
        return SETSOCKOPT_ERROR;
    }
    if(bind(sfd, (struct sockaddr*)addr,sizeof(struct sockaddr_in))!= 0)
    {
        return BIND_ERROR;
    }
    return TCP_OK;
}
int ListenSocket(int sfd)
{
    if(listen(sfd,BACKLOG)!= 0)
    {
        return LISTEN_ERROR;
    }
    return TCP_OK;
}

int AcceptData(int sfd, void* addr, socklen_t* length,int* inner)
{
    int flags;
    if(length == NULL || inner == NULL)
    {
        return INVALID_ARGUMENT_ERROR;
    }
    *inner = accept(sfd, (struct sockaddr*)addr, length);
    printf("new clients accepted\n");
    if(*inner < 0)
    {
        return ACCEPT_ERROR;
    }
    if(FAIL==(flags = fcntl(sfd, F_GETFL)))
    {
        return ACCEPT_ERROR;
    }
    if(FAIL==fcntl(*inner,F_SETFL ,flags|O_NONBLOCK))
    {
        return ACCEPT_ERROR;
    }
    return TCP_OK;
}

int Connect(int sfd, void* addr, int length)
{
    if(addr == NULL)
    {
        return INVALID_ARGUMENT_ERROR;
    }
    if(connect(sfd, (struct sockaddr*)addr, length) != 0)
    {
        return CONNECT_ERROR;
    }
    return TCP_OK;
}

ssize_t readFrom(int sfd, char*  buf, int length)
{
    if(buf == NULL)
    {
        return INVALID_ARGUMENT_ERROR;
    }
    return read(sfd, buf, length);
}
ssize_t writeTo(int sfd, char* buf, int length)
{
    if(buf == NULL)
    {
        return INVALID_ARGUMENT_ERROR;
    }
    return write(sfd, buf, length);
}

void closeSocket(int sfd)
{
    close(sfd);
}