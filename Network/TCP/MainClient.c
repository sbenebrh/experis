
#include <sys/types.h> 
#include <sys/socket.h>
#include <stdio.h>

#include "Client.h"

int main()
{
    struct sockaddr_in servaddr; 
    FillServerInfo(&servaddr,AF_INET,1234,"127.0.0.1");
    Run(&servaddr,AF_INET,1234,"127.0.0.1");
    
}