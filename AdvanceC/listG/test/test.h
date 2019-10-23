#ifndef __LIST_TEST_H__
#define __LIST_TEST_H__

#include"list.h"

typedef enum 
{
	SUCCEED,
	FAIL
}TestResult;

TestResult TestCreatelist();
TestResult TestPushHead1(List_Result* _status);
TestResult TestPushHead2(List_Result* _status);
TestResult TestPushHead3(List_Result* _status);
TestResult TestPushTail1(List_Result* _status);

#endif