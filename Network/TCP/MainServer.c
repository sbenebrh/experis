
#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h>
#include "Server.h"

int main()
{
    int sfd;
    int connfd;
    sfd = InitServer(AF_INET,1234,"127.0.0.1");
    /*connfd  = ConnectServer(sfd);*/
    DataTransfer(sfd);
    
    End(connfd);
}