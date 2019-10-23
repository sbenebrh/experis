#ifndef __TEST_BST_H__
#define __TEST_BST_H__


#include"bin_tree.h"

typedef enum 
{
	SUCCEED,
	FAIL
}TestResult;

TestResult TestBstCreate1();
TestResult TestBstDestroy1();
TestResult TestBstDestroy2();
TestResult TestBstInsert1();
TestResult TestBstInsert2();
TestResult TestBstInsert3();
TestResult TestBstFindFirst1();
TestResult TestBstFindFirst2();
TestResult TestBstFindFirst3();
TestResult TestBstBegin1();
TestResult TestBstBegin2();
TestResult TestBstBegin3();
TestResult TestBstForEach1();
TestResult TestBstEqual1();
TestResult TestBstEqual2();



#endif