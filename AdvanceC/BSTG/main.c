#include<stdio.h>
#include"test.h"

void PrintResult(char* _testName, TestResult _result)
{
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

int main()
{
	PrintResult("TestBstCreate1", TestBstCreate1());
	PrintResult("TestBstDestroy1", TestBstDestroy1());
	PrintResult("TestBstDestroy2", TestBstDestroy2());
	PrintResult("TestBstInsert1", TestBstInsert1());
	PrintResult("TestBstInsert2", TestBstInsert2());
	PrintResult("TestBstInsert3", TestBstInsert3());
	PrintResult("TestBstFindFirst1", TestBstFindFirst1());
	PrintResult("TestBstFindFirst2", TestBstFindFirst2());
	PrintResult("TestBstFindFirst3", TestBstFindFirst3());
	PrintResult("TestBstBegin1", TestBstBegin1());
	PrintResult("TestBstBegin2", TestBstBegin2());
	PrintResult("TestBstBegin3", TestBstBegin3());
	PrintResult("TestBstForEach1", TestBstForEach1());
	PrintResult("TestBstEqual1", TestBstEqual1());
	PrintResult("TestBstEqual2", TestBstEqual2());
	return 0;
}