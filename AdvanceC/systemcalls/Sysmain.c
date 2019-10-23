#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main()
{	
	int i;
	pid_t pid = fork();

	/*father*/
	if(pid > 0)
	{
		for(i = 5;i > 0;--i)
		{
			printf("i am the parent: %ud\n" ,getpid() );
			sleep(3);
		}
	}
	else
	{
		
			printf( "i am the child: %ud\n" ,getpid());
			char *newargv[] = {"/home/samuel/work/AdvanceC/vectorG/vector"};
			char *newenviron[] = { NULL };
			execve("/home/samuel/work/AdvanceC/vectorG/vector", newargv, newenviron);
			sleep(1);
		
	}
	return 0;
}