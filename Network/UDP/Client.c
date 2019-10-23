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
    int n = 0, len ; 
    char buffer[MAXLINE]; 
    char *hello = "Hello from client"; 
    struct sockaddr_in     servaddr; 
    memset(&servaddr, 0, sizeof(servaddr)); 

    // Creating socket file descriptor 
    if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
        perror("socket creation failed"); 
        exit(EXIT_FAILURE); 
    } 
  
    
      
    // Filling server information 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_port = htons(PORT); 
    servaddr.sin_addr.s_addr = inet_addr("127.0.0.1"); 
      
    
      
    sendto(sockfd, hello, strlen(hello), 
        0, (const struct sockaddr *) &servaddr,  
            sizeof(servaddr)); 
    printf("Hello message sent.\n"); 
    
    n = recvfrom(sockfd,buffer, MAXLINE,  
                0, (struct sockaddr *) &servaddr, 
                &len); 
    buffer[n] = '\0'; 
    printf("Server : %s\n", buffer); 
  
    close(sockfd); 
    return 0; 
} 