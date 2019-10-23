// this is demo code and not prosuctuion code dont ever use it in production
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
int sum = 0;

void * ThreadFunction1(void *arg)
{
    int j;
	puts("Hello world from thread1\n");
	for (int i = 0; i<10; i++) {
        j = sum;
        j++;
        sleep(0);
        sum = j;
 	}
	puts("Exiting thread 1\n");
	return(NULL);
}

void * ThreadFunction2(void *arg)
{
   int j;
	puts("Hello world from thread2\n");
	for (int i = 0; i<10; i++) {
        j = sum;
        j++;
        sleep(0);
        sum = j;
 	}
	puts("Exiting thread 2\n");
	return(NULL);
}

void * ThreadFunction3(void *arg)
{
   int j;
	puts("Hello world from thread3\n");
	for (int i = 0; i<10; i++) {
        j = sum;
        j++;
        sleep(0);
        sum = j;
 	}
	puts("Exiting thread 3\n");
	return(NULL);
}

void * ThreadFunction4(void *arg)
{
   int j;
	puts("Hello world from thread4\n");
	for (int i = 0; i<10; i++) {
        j = sum;
        j++;
        sleep(0);
        sum = j;
 	}
	puts("Exiting thread 4\n");
	return(NULL);
}
void * ThreadFunction5(void *arg)
{
    int j;
	puts("Hello world from thread1\n");
	for (int i = 0; i<10; i++) {
        j = sum;
        j++;
        sleep(0);
        sum = j;
 	}
	puts("Exiting thread 1\n");
	return(NULL);
}

void * ThreadFunction6(void *arg)
{
   int j;
	puts("Hello world from thread2\n");
	for (int i = 0; i<10; i++) {
        j = sum;
        j++;
        sleep(0);
        sum = j;
 	}
	puts("Exiting thread 2\n");
	return(NULL);
}

void * ThreadFunction7(void *arg)
{
   int j;
	puts("Hello world from thread3\n");
	for (int i = 0; i<10; i++) {
        j = sum;
        j++;
        sleep(0);
        sum = j;
 	}
	puts("Exiting thread 3\n");
	return(NULL);
}

void * ThreadFunction8(void *arg)
{
   int j;
	puts("Hello world from thread4\n");
	for (int i = 0; i<10; i++) {
        j = sum;
        j++;
        sleep(0);
        sum = j;
 	}
	puts("Exiting thread 4\n");
	return(NULL);
}



int main()
{
	int retval;
	pthread_t Thread1,Thread2,Thread3,Thread4;
	void * Arg = NULL;
	puts("Hello world!\n");
	puts("CreatingThread 1\n");
	retval = pthread_create(&Thread1, NULL, ThreadFunction1, Arg);
	puts("Thread 1 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", Thread1);
	puts("CreatingThread 2\n");
	retval = pthread_create(&Thread2, NULL, ThreadFunction2, Arg);
	puts("Thread 2 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", Thread2);
	puts("CreatingThread 3\n");
	retval = pthread_create(&Thread3, NULL, ThreadFunction3, Arg);
	puts("Thread 3 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", Thread3);
	puts("CreatingThread 4\n");
	retval = pthread_create(&Thread4, NULL, ThreadFunction4, Arg);
	puts("Thread 4 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", Thread4);
	puts("CreatingThread 5\n");
	retval = pthread_create(&Thread1, NULL, ThreadFunction5, Arg);
	puts("Thread 1 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", Thread1);
	puts("CreatingThread 6\n");
	retval = pthread_create(&Thread2, NULL, ThreadFunction6, Arg);
	puts("Thread 2 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", Thread2);
	puts("CreatingThread 7\n");
	retval = pthread_create(&Thread3, NULL, ThreadFunction7, Arg);
	puts("Thread 3 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", Thread3);
	puts("CreatingThread 8\n");
	retval = pthread_create(&Thread4, NULL, ThreadFunction8, Arg);
	puts("Thread 4 Created\n");
	printf("retval from pthread_create is %i \n", retval);
	printf("pthread_t is %lu \n", Thread4);

	for (int i = 0; i<10; i++) {
        sum++ ;
    }
	puts("Press ENTER when all threads finished\n");
	getchar();
    printf("sum is %d\n", sum);
	puts("Press ENTER to exit\n");
	getchar();
	puts("Exiting Program\n");
	return 0;
}
