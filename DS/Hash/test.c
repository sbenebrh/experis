#include<stdio.h>
#include<stdlib.h>
#include"hash.h"
#include"ADTErr.h"


static void PrintResult(char* _testName, TestResult _result, ADTErr _stat)
{
	if(_stat != ERR_OK) printf("%s %s \n","test error of the", _testName );
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

TestResult Test_hashBuild1()
{
	Hash * new_hash = HashCreate(1);

	if(NULL == new_hash)
	{
		return FAIL;
	}
	
	HashDestroy(new_hash);
	
	return SUCCEED;
}
TestResult Test_hashBuild2()
{
	Hash * new_hash = HashCreate(0);

	if(NULL == new_hash)
	{
		return SUCCEED;
	}
	
	return FAIL;
}
TestResult Test_hashInsert(ADTErr* status)
{
	int i;
	int arr[5] = { 3 , 11 , 8 , 17, 18};

	Hash * new_hash = HashCreate(5);

	if(NULL == new_hash)
	{
		return FAIL;
	}
	

	for(i = 0; i < 5 ; i++)
	{	
		*status |= HashInsert(new_hash, arr[i]);
	}
	HashPrint(new_hash);

	HashDestroy(new_hash);
	
	return *status == ERR_OK ? SUCCEED:FAIL;

}

TestResult Test_hashDestroy1()/*test apply destroy twice*/
{
	Hash * new_hash = HashCreate(5);
	if(NULL == new_hash)
	{
		return FAIL;
	}
	
	HashDestroy(new_hash);
	HashDestroy(new_hash);
	
	return SUCCEED;
}



int main()
{
	ADTErr stat = 0;
	TestResult res;
	PrintResult("Test_hashBuild1", Test_hashBuild1(),ERR_OK);
	
	res = Test_hashBuild2(&stat);
	PrintResult("\nTest_hashBuild2", res,stat);

	PrintResult("Test_hashDestroy1", Test_hashDestroy1(),ERR_OK);

	res = Test_hashDestroy1(&stat);
	PrintResult("Test_hashDestroy1", res,stat);

	res = Test_hashInsert(&stat);
	PrintResult("Test_hashInsert", res,stat);

	
	return 0;
}