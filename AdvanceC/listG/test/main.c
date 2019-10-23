#include <stdio.h>

#include"test.h"
void PrintResult(char* _testName, TestResult _result, List_Result  _stat)
{
	if(_stat != LIST_SUCCESS) 
		{
			printf("%s %s \n","test error of the", _testName );
		}

	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}
int main()
{
	List_Result status;
	TestResult result;

	PrintResult("TestCreatelist",TestCreatelist(&status), LIST_SUCCESS);
	
	result = TestPushHead1(&status);
	PrintResult("TestPushHead1",result, status);
	return 0;
}