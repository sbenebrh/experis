#include<stdio.h>
#include"Executor.h"
#include"zlog4c.h"
	

int funcA(void* _context)
{
	static int a = 2;
	printf("%s\n", "HELLO i am A");
	a--;
	return a? 1:0;
}

int funcB(void* _context)
{
	static int a = 2;
	printf("%s\n", "HELLO i am B");
	a--;
	return a? 1:0;
}
int funcC(void* _context)
{
	static int a = 2;
	printf("%s\n", "HELLO i am C");
	a--;
	return a? 1:0;
}
int main()
{
	zlog_init("/home/samuel/work/AdvanceC/Executor/logConfig");
	Executor* test = Executor_Create(2, 1);
	Executor_AddTask(test,funcA,3,NULL);
	Executor_AddTask(test, funcB, 5, NULL);
	Executor_AddTask(test, funcC, 5, NULL);

	Executor_Run(test);
	Executor_Destroy(test);
	return 0;
}
