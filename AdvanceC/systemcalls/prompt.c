#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

static int  IsEmptyAction(char* _action)
{
	return !strlen(_action);
}
static void printCurrentDirectory()
{
	char* dir = malloc(64 * sizeof(char));
	printf("%s>:",getcwd(dir,64) );
}
int main()
{
	while(1)
	{
		pid_t pid;
		char* action = malloc(64*sizeof(char));
		printCurrentDirectory();
		fgets(action,64,stdin);
		
		if(IsEmptyAction(action))
		{
			continue;
		}
		strtok(action,"\n");
		/*the user write exit*/
		if(!strcmp(action,"exit"))
		{
			exit(0);
		}
		pid = fork();
		if(pid > 0)
		{
			wait(NULL);
		}else
		{
			char *newargv[] = {action};
			char *newenviron[] = { NULL };
			execve(action, &newargv[0], newenviron);
			exit(0);
		}

	}
	return 0;
}