#include <stdio.h>
#include <signal.h>
#include <unistd.h>

static void hdl (int sig, siginfo_t *siginfo, void *context)
{
	write(1, "I DONT WANT TO EXIT\n", 20);
}
int main()
{
	struct sigaction act;
	act.sa_sigaction = &hdl;	
	act.sa_flags = SA_SIGINFO;


	while(1)
	{
		sleep(10);
		if (sigaction(SIGTERM, &act, NULL) < 0) 
		{
			perror ("sigaction");
			return 1;
		}
		printf("%s\n", "i am main");
		fflush(stdout);

	}

	return 0;

}