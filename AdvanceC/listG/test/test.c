#include<stdlib.h>
#include"list.h"
#include "test.h"

TestResult TestCreatelist()/* check if when i create list i get not null pointer*/
{
	TestResult res;
	List* newList = List_Create();
	if(newList)
	{
	 	res = SUCCEED;
	}
	else
	{
		res = FAIL;
	}
	List_Destroy(&newList,NULL);
	return res;

}
TestResult TestPushHead1(List_Result* _status)/*check if with the push head i can add one item*/
{
	int a = 1;
	List* newList = List_Create();
	*_status = List_PushHead(newList, &a);

	List_Destroy(&newList,NULL);

	return *_status == LIST_SUCCESS ? SUCCEED:FAIL;
}/*
TestResult TestPushHead2(Vector_Result* _status)/*check if with the push head i can add more than one item and keep the insert order
{
	List* newList = ListCreate();
	*_status = ListPushHead(newList, 1);
	*_status |= ListPushHead(newList, 2);
	*_status |= ListPushHead(newList, 3);

	ListPrint(newList);

	ListDestroy(newList);

	return *_status == LIST_SUCCESS ? SUCCEED:FAIL;
}
TestResult TestPushHead3(Vector_Result* _status)check if i can push to the unitialized list
{
	List* newList = NULL;
	*_status = ListPushHead(newList, 1);

	return *_status != LIST_SUCCESS ? SUCCEED:FAIL;
}
TestResult TestPushTail1(Vector_Result* _status)/*check if with the push head i can add one item
{
	List* newList = ListCreate();
	*_status = ListPushTail(newList, 1);

	ListPrint(newList);

	ListDestroy(newList);

	return *_status == LIST_SUCCESS ? SUCCEED:FAIL;
}
TestResult TestPushTail2(Vector_Result* _status)/*check if with the push head i can add more than one item and keep the insert order
{
	List* newList = ListCreate();
	*_status = ListPushTail(newList, 1);
	*_status |= ListPushTail(newList, 2);
	*_status |= ListPushTail(newList, 3);

	ListPrint(newList);

	ListDestroy(newList);

	return *_status == LIST_SUCCESS ? SUCCEED:FAIL;
}
TestResult TestPushTail3(Vector_Result* _status)/*check if i can push to the unitialized list
{
	List* newList = NULL;
	*_stat = ListPushTail(newList, 1);

	return *_status != LIST_SUCCESS ? SUCCEED:FAIL;
}
TestResult TestPushRegression(Vector_Result* _status)
{
		List* newList = ListCreate();
	*_status = ListPushTail(newList, 1);
	*_status |= ListPushHead(newList, 2);
	*_status |= ListPushTail(newList, 3);
	*_status |= ListPushHead(newList, 4);
	ListPrint(newList);

	ListDestroy(newList);

	return *_status == LIST_SUCCESS ? SUCCEED:FAIL;
}*/