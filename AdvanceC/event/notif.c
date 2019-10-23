#include <sys/types.h>/*opendir*/
#include <dirent.h>/*struct dirent*/
#include <stdio.h>/*printf*/
#include <sys/inotify.h>/*inotify_init*/
#include <unistd.h>/*read*/


#define EVENT_SIZE 		(sizeof(struct inotify_event))
#define BUF_LEN			(1024 *(EVENT_SIZE + 16))

void printFileName(char* filename)
{
	DIR* d;
	struct dirent *_dir;
	d = opendir(filename);
	if(NULL == d)
	{
		perror("opendir");
	}

	while((_dir= readdir(d))!= NULL)
	{
		printf("%s\t", _dir -> d_name);
		fflush(stdout);
	}
	closedir(d);
}

void MonitorFileSystem(char* _foldername)
{
	int fd, wd;
	size_t length = 0;
	char buffer[BUF_LEN];
	struct inotify_event *event;

	fd = inotify_init();
	if(fd < 0)
	{
		perror("inotify_init");
	}
	printFileName(_foldername);


	wd = inotify_add_watch(fd,_foldername, IN_CREATE | IN_MODIFY | IN_DELETE);
	if(wd < 0)
	{
		perror("inotify_add_watch");
	}

	while(1)
	{
		length = read( fd, buffer, BUF_LEN );
		if(length < 0)
		{
			perror("read");
			break;
		}
		event = ( struct inotify_event * ) & buffer[ 0 ];
	    if ( event->len ) 
	    {
	      	if ( event->mask & IN_CREATE ) 
	      	{
	          	printf( "The file %s was created.\n", event->name );
	        }
	      	else if ( event->mask & IN_DELETE ) 
	      	{
	          	printf( "The file %s was deleted.\n", event->name );
	      	}
	      	else if ( event->mask & IN_MODIFY ) 
	      	{
	          	printf( "The file %s was modified.\n", event->name );    		
	      	}
	    }
 	}
	
    ( void ) inotify_rm_watch( fd, wd );
  	( void ) close( fd );
}
