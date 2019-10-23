#include <stdlib.h>  		/*exit*/
#include <stdio.h>
#include <string.h>			/*strcat*/
#include <sys/wait.h>		/*wait*/
#include <unistd.h>         /*fork()*/
#include <sys/inotify.h>    /*inotify functions*/
#include <libconfig.h> 		/*parse config file*/


#define CONFIG_FILE "../config.txt"
#define NUM_CONFIG_PARAMS 3

#define FILE_PATH_SIZE 512
#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024 * (EVENT_SIZE+16))  		/* The len field counts all of the bytes in name, including the null
      												 bytes; the length of each inotify_event structure is thus:
       												 sizeof(struct inotify_event)+len*/


/*
struct inotify_event 
{
  int wd;            	The watch descriptor 
  uint32_t mask;     	Watch mask 
  char name __flexarr;  The name of the file, padding to the end with null bytes
  uint32_t cookie;  	A cookie to tie two events together 
  uint32_t len;     	The length of the filename found in the name field 
}
*/

/*get configuration parameters*/
char** GetConfig(config_t* cfg);


int main(int argc, char* argv[])
{
	int i=0;
	int fd,wd;
	int length;
	char buffer[BUF_LEN];
	struct inotify_event* event;

	pid_t childPid;
	char* argVec[4];
	char inPath[FILE_PATH_SIZE];
	char donePath[FILE_PATH_SIZE];
	config_t cfg;
	char** configArr;
	
	/*read config params*/
	configArr=GetConfig(&cfg);

	/*setup params for child processes*/

	argVec[0]=configArr[0];
	argVec[3]=NULL;

	/*create inotify instance*/
	fd=inotify_init();
	if(fd==-1)
	{
		perror("inotify_init\n");
		exit(1);
	}
	/*add watch to monitor arrival of cdr files*/
	wd=inotify_add_watch(fd, configArr[1], IN_MOVED_TO);

	while(1)
	{	
		/*read- blocks the program until an alert arrives.
		  By default, read() waits until at least one byte is available to return to the application*/
		length=read(fd,buffer,BUF_LEN);
		if(length<0)
		{
			perror("read\n");
			exit(1);
		}
		/*length is the total number of bytes read. i advanvces from one event to the next
		  This loops handles the case where multiple files were added simultaneously to the directory*/
		while(i<length)
		{	
			event=(struct inotify_event*) &buffer[i];	
			/*The len field counts all of the bytes in name. so len>0 indicates we have an event*/
		  	if(event->len) 
			{
			  if(event->mask & IN_MOVED_TO) 
			  {
					/*setup params for child processes*/
					strcpy(inPath,configArr[1]);
					strcat(inPath,event->name);
					argVec[1]=inPath;
					strcpy(donePath,configArr[2]);
					strcat(donePath,event->name);
					argVec[2]=donePath;
					childPid=fork();
					switch(childPid)
					{
						case -1: perror("fork\n");
								 exit(1);
						/*child process executes fHandler program*/
						case 0: 
							printf("%s\n",argVec[0]);
							execve(argVec[0],argVec,NULL);	
							break;				
					}
			  }
			} 
			/*the length of each inotify_event structure is: sizeof(struct inotify_event)+len
              here we move to the next event in the buffer*/
			i += EVENT_SIZE + event->len;

		} /*end inner while */	 
		i=0;
	}/*end outer while */	

	/*remove watch and close the file descriptor*/
	inotify_rm_watch(fd,wd);
	close(fd);
	/*destroy config*/
	config_destroy(&cfg);
	free(configArr);

	/*wait for all child processes (file handlers) to terminate*/  
	while ((childPid = wait(NULL)) != -1)
	{ 
		continue;
	}
	return(0);
}

		


char** GetConfig(config_t* cfg)
{
    config_setting_t* setting;
	char** configArr;

	/*malloc since we need the params visible in the main scope*/
	configArr=(char**) malloc(NUM_CONFIG_PARAMS*sizeof(char*));
	config_init(cfg);
	if(!config_read_file(cfg,CONFIG_FILE))
	{	
		printf("%s:%d - %s\n", config_error_file(cfg), config_error_line(cfg), config_error_text(cfg));
        config_destroy(cfg);
        exit(1);
	}

	setting=config_lookup(cfg,"input");
	if(setting)
	{	
		if(!config_setting_lookup_string(setting, "handler", &configArr[0]))
		{
            printf("No 'handler' setting in configuration file.");
			config_destroy(cfg);
	        exit(1);
		}

		if(!config_setting_lookup_string(setting, "inDir", &configArr[1]))
		{
            printf("No 'directory' setting in configuration file.");
			config_destroy(cfg);
	        exit(1);
		}

		if(!config_setting_lookup_string(setting, "doneDir", &configArr[2]))
		{
            printf("No 'done' setting in configuration file.");
			config_destroy(cfg);
	        exit(1);
		}
	}	
	return configArr;
}







