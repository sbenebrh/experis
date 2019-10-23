#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 16
#define FDPIPE	2
static int pipeCreate(int pfd1[], int pfd2[])
{
	int status = 0;
	if ((status = pipe(pfd1)) < 0) 
	{
	   perror("pipe1");
	   return status;
	}
	if ((status = pipe(pfd2)) < 0) 
	{
	   perror("pipe1");
	   return status;
	}
	return status;
}

static void childProcess(int pfd1[], int pfd2[], char* buffer)
{
	if(close(pfd1[1]) <0)
	{
		perror("close pipe");
	}		
	if(read(pfd1[0],buffer,BUFFER_SIZE) <0)
	{
		perror("read");
	}
	printf("i receive this message from my father %s\n",buffer );

	if(close(pfd2[0]) <0)
	{
		perror("close pipe");
	}	
	if(write(pfd2[1], "world ",BUFFER_SIZE)< 0)
	{
		perror("read");
	}
	if(close(pfd2[1]) <0)
	{
		perror("close pipe");
	}	
}

static void parentProcess(int pfd1[], int pfd2[], char* buffer)
{
	if(close(pfd1[0]) <0)
	{
		perror("close reading pipe");
	}

	if(write(pfd1[1], "hello ",BUFFER_SIZE)< 0)
	{
		perror("write");
	}
	/*wait(NULL);*/
	if(close(pfd2[1]) <0)
	{
		perror("close writting end pipe");
	}
	if(read(pfd2[0],buffer,BUFFER_SIZE) <0)
	{
		perror("read");
	}

	if(close(pfd2[0]) <0)
	{
		perror("close reading end pipe");
	}
	printf("i receive this message from my son %s\n",buffer );
	close(pfd1[1]);
}

static void ping_pong()
{
	pid_t pid;
	int pipefd[FDPIPE];
	int pipefd2[FDPIPE];
	char *buffer = (char*) malloc (BUFFER_SIZE * sizeof(char));
	char *buffer2 = (char*) malloc (BUFFER_SIZE * sizeof(char));

	if(pipeCreate(pipefd,pipefd2) < 0)
	{
		exit(EXIT_FAILURE);
	}

	switch(pid = fork())
	{
		case -1:
		 	perror("fork");
	   		exit(EXIT_FAILURE);
	   	case 0:  

	   		
	   		printf("%s\n","i am the son and i receive signal from my father" ); 

	   		childProcess(pipefd, pipefd2, buffer);
	   		
			exit(0);

	   	default:
	   	
	   		printf("%s\n","i am the father and i send signal to my father" ); 

	   		parentProcess(pipefd, pipefd2, buffer2);
	}
	free(buffer);
	free(buffer2);
}
int main()
{
	ping_pong();
	return 0;
	
}


