 
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
  
#define PORT     12345
#define MAXLINE 64 
  

int main() { 
    int sockfd = 0;
     
    char buffer[MAXLINE]; 
    char *hello = "Hello from server"; 
    struct sockaddr_in servaddr, cliaddr; 
    int len = sizeof(servaddr) , n = 0; 
    memset(&servaddr, 0, sizeof(servaddr)); 
    memset(&cliaddr, 0, sizeof(cliaddr)); 

    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    
      
    // Filling server information 
    servaddr.sin_family    = AF_INET; // IPv4 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
    servaddr.sin_port = htons(PORT); 
      
    // Bind the socket with the server address 
    if ( bind(sockfd, (const struct sockaddr *)&servaddr,  
            sizeof(servaddr)) < 0 ) 
    { 
        perror("bind failed"); 
        exit(EXIT_FAILURE); 
    } 
      
    while(1)
    {
        n = recvfrom(sockfd, buffer, MAXLINE,  
                    0, ( struct sockaddr *) &cliaddr, 
                    &len); 
        buffer[n] = '\0'; 
        printf("Client : %s\n", buffer); 
        sendto(sockfd, hello, strlen(hello),  
            0, (const struct sockaddr *) &cliaddr, 
                sizeof(cliaddr)); 
        printf("Hello message sent.\n");  
    }
    return 0; 
}