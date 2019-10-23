#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

#define MESS_SIGNAL_CTP		"TAKE IT \n"
#define MESS_SIGNAL_PTC		"NO WAY\n"
/*#########################STATIC#####################*/
static void hdl (int sig, siginfo_t *siginfo, void *context);
static void hdl1(int sig, siginfo_t *siginfo, void *context);
static void parent_process(pid_t pid);
static void child_process(pid_t pid);
static void signal_pingpong();
/*######################################################*/

int main()
{
	signal_pingpong();
	return 0;
}



/*################STATIC############################*/
static void signal_pingpong()
{
	pid_t pid;
	switch(pid = fork())
	{
		case -1 :
			perror("fork");
			return;
		case 0:

		child_process(pid);
		exit(EXIT_SUCCESS);	

		default:
			parent_process(pid);
			exit(EXIT_SUCCESS);
	}
}

static void child_process(pid_t pid)
{
	struct sigaction act1;
	act1.sa_sigaction = &hdl;	
	act1.sa_flags = SA_SIGINFO;

	if (sigaction(SIGTERM, &act1, NULL) < 0) 
	{
		sleep(3);
		perror ("sigaction\n");
	}
	sleep(10);
}
static void parent_process(pid_t pid)
{
	struct sigaction act2;
	act2.sa_sigaction = &hdl1;
	act2.sa_flags = SA_SIGINFO;
                                                                                                                      
	if (sigaction(SIGUSR1, &act2, NULL) < 0) 
	{
		sleep(3);
		perror ("sigaction\n");
	}
	sleep(5);
	if(kill(pid, SIGTERM) < 0)
	{
		perror("kill father");
	}
	wait(NULL);	
}

static void hdl (int sig, siginfo_t *siginfo, void *context)
{
	write(1, MESS_SIGNAL_CTP, sizeof(MESS_SIGNAL_CTP));
	
	if(kill(siginfo -> si_pid, SIGUSR1) == -1)
	{
		perror("kill child");
	} 
}
static void hdl1(int sig, siginfo_t *siginfo, void *context)
{
	sleep(2);
	write(1, MESS_SIGNAL_PTC, sizeof(MESS_SIGNAL_PTC));
}




