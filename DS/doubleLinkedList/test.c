#include<stdio.h>
#include<stdlib.h>
#include"doubleList.h"
#include"ADTErr.h"
void PrintResult(char* _testName, TestResult _result, ADTErr _stat)
{
	if(_stat != ERR_OK) printf("%s %s \n","test error of the", _testName );
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

TestResult TestCreatelist()/* check if when i create list i get not null pointer*/
{
	TestResult res;
	List* newList = ListCreate();
	if(newList)
	{
	 	res = SUCCEED;
	}
	else
	{
		res = FAIL;
	}
	ListDestroy(newList);
	return res;

}
TestResult TestPushHead1(ADTErr* _stat)/*check if with the push head i can add one item*/
{
	List* newList = ListCreate();
	*_stat = ListPushHead(newList, 1);

	ListPrint(newList);

	ListDestroy(newList);

	return *_stat == ERR_OK ? SUCCEED:FAIL;
}
TestResult TestPushHead2(ADTErr* _stat)/*check if with the push head i can add more than one item and keep the insert order*/
{
	List* newList = ListCreate();
	*_stat = ListPushHead(newList, 1);
	*_stat |= ListPushHead(newList, 2);
	*_stat |= ListPushHead(newList, 3);

	ListPrint(newList);

	ListDestroy(newList);

	return *_stat == ERR_OK ? SUCCEED:FAIL;
}
TestResult TestPushHead3(ADTErr* _stat)/*check if i can push to the unitialized list*/
{
	List* newList = NULL;
	*_stat = ListPushHead(newList, 1);

	return *_stat != ERR_OK ? SUCCEED:FAIL;
}
TestResult TestPushTail1(ADTErr* _stat)/*check if with the push head i can add one item*/
{
	List* newList = ListCreate();
	*_stat = ListPushTail(newList, 1);

	ListPrint(newList);

	ListDestroy(newList);

	return *_stat == ERR_OK ? SUCCEED:FAIL;
}
TestResult TestPushTail2(ADTErr* _stat)/*check if with the push head i can add more than one item and keep the insert order*/
{
	List* newList = ListCreate();
	*_stat = ListPushTail(newList, 1);
	*_stat |= ListPushTail(newList, 2);
	*_stat |= ListPushTail(newList, 3);

	ListPrint(newList);

	ListDestroy(newList);

	return *_stat == ERR_OK ? SUCCEED:FAIL;
}
TestResult TestPushTail3(ADTErr* _stat)/*check if i can push to the unitialized list*/
{
	List* newList = NULL;
	*_stat = ListPushTail(newList, 1);

	return *_stat != ERR_OK ? SUCCEED:FAIL;
}
TestResult TestPushRegression(ADTErr* _stat)
{
		List* newList = ListCreate();
	*_stat = ListPushTail(newList, 1);
	*_stat |= ListPushHead(newList, 2);
	*_stat |= ListPushTail(newList, 3);
	*_stat |= ListPushHead(newList, 4);
	ListPrint(newList);

	ListDestroy(newList);

	return *_stat == ERR_OK ? SUCCEED:FAIL;
}
TestResult TestPopHead1(ADTErr* _stat)
{
	List* newList = ListCreate();
	*_stat = ListPop(newList)
}
int main()
{
	ADTErr status ;
	TestResult res;

	PrintResult("TestCreatelist", TestCreatelist(),ERR_OK);
	res = TestPushHead1(&status);
	PrintResult("TestPushHead1",res ,status);
	res = TestPushHead2(&status);
	PrintResult("TestPushHead2", res,status);
	res = TestPushHead3(&status);
	PrintResult("TestPushHead3", res,ERR_OK);
	res = TestPushTail1(&status);
	PrintResult("TestPushTail1",res ,status);
	res = TestPushTail2(&status);
	PrintResult("TestPushTail2", res,status);
	res = TestPushTail3(&status);
	PrintResult("TestPushTail3", res,ERR_OK);
	res = TestPushRegression(&status);
	PrintResult("TestPushRegression", res,ERR_OK);
	return 0;
}
