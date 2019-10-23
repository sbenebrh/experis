#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <semaphore.h>

#define FILENAME "thread.txt"
#define OBJ_PERMS 			S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP
sem_t sem;

struct threadArgs
{
	int count;
};
void* printThread3()
{	
	sleep(0);
	return NULL;
}
void* printThread4(void* arg)
{
	int i = 0;

	printf("%s%d\n","i am :",(*(int*)arg) );
	sem_post(&sem);
	return NULL;
}
void* printThread1()
{
	int i = 0;
	for(i = 0; i < 10;++i)
	{
		printf("%s\n","i am 1" );
		sleep(1);
	}
	return NULL;
}
void* printThread2()
{
	int i = 0;
	for(i = 0; i < 5;++i)
	{
		printf("%s\n","i am 2" );
		sleep(2);
	}
	return NULL;
}

/*int main()
{
   pthread_t thread1, thread2;

    if(pthread_create(&thread1,NULL, printThread1, NULL) != 0)
    {
    	perror("create thread");
    	exit(1);
    }
    if(pthread_create(&thread2,NULL, printThread2, NULL) != 0)
    {
    	perror("create thread");
    	exit(1);
    }
    
  	if(pthread_join(thread1,NULL) != 0)
  	{
  		perror("join");
  		exit(1);
  	}

    if(pthread_join(thread2,NULL) != 0)
  	{
  		perror("join");
  		exit(1);
  	}
	return 0;

}*/
/*
int main()
{
	int count = 0;
	pthread_t thread1;

	while(1)
	{
		if(pthread_create(&thread1,NULL, printThread3, NULL) != 0)
    	{
    		printf("%d\n",count);
    		perror("create thread");
    		exit(1);
   		}
   		pthread_join(thread1,NULL);
   		count ++;
   		if(count > 1000000000)
   		{
   			printf("%d\n",count );
   			break;
   		}
	}

}*/

int main()
{
	int numberOfthread = 10;
	int i = 0;
	struct threadArgs args;
	args.count = 0;
	pthread_t thread1;
	int nums[numberOfthread];
	
	if(sem_init(&sem,0,0) < 0)
	{
		perror("sem_init");
		exit(1);
	}

	for(i = 0; i < numberOfthread; ++i)
	{
		nums[i] = i;
	}
	for(i = 0;i < numberOfthread;++i)
	{
		
		if(pthread_create(&thread1,NULL, printThread4, &i) != 0)
    	{
    		perror("create thread");
    		exit(1);
   		}
   		if(sem_wait(&sem) != 0)
		{
			perror("sem_wait");
			exit(1);
		}
	}
	return 0;
}