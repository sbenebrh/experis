
#include<stdio.h>
#include"test.h"
#include"vector.h"


void PrintResult(char* _testName, TestResult _result, Vector_Result  _stat)
{
	if(_stat != VECTOR_SUCCESS) 
		{
			printf("%s %s \n","test error of the", _testName );
		}

	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}

int main()
{
	Vector_Result status;
	TestResult result;
	PrintResult("TestVecCreate1",TestVecCreate1(&status), VECTOR_SUCCESS);
	PrintResult("TestVecCreate2",TestVecCreate2(&status), VECTOR_SUCCESS);
	PrintResult("TestVecCreate3",TestVecCreate3(&status), VECTOR_SUCCESS);
	PrintResult("TestVecCreate4",TestVecCreate4(&status), VECTOR_SUCCESS);

	PrintResult("TestVecDestroy1",TestVecDestroy1(&status), VECTOR_SUCCESS);
	PrintResult("TestVecDestroy2",TestVecDestroy2(&status), VECTOR_SUCCESS);

	PrintResult("TestVecAppend1",TestVecAppend1(&status), VECTOR_SUCCESS);
	PrintResult("TestVecAppend2",TestVecAppend2(&status), VECTOR_SUCCESS);
	PrintResult("TestVecAppend3",TestVecAppend3(&status), VECTOR_SUCCESS);
	PrintResult("TestVecAppend4",TestVecAppend4(&status), VECTOR_SUCCESS);
	PrintResult("TestVecAppend5",TestVecAppend5(&status), VECTOR_SUCCESS);


	result = TestVecRemove1(&status);
	PrintResult("TestVecRemove1",result, VECTOR_SUCCESS);
	result = TestVecRemove2(&status);
	PrintResult("TestVecRemove2",result, status);
	result = TestVecRemove3(&status);
	PrintResult("TestVecRemove3",result, status);


	PrintResult("TestVecGet1",TestVecGet1(&status), VECTOR_SUCCESS);
	PrintResult("TestVecGet2",TestVecGet2(&status), VECTOR_SUCCESS);

	result = TestVecSet1(&status);
	PrintResult("TestVecSet1",result, VECTOR_SUCCESS);
	result = TestVecSet2(&status);
	PrintResult("TestVecSet2",result, status);

	result = TestVecAppend11(&status);
	PrintResult("TestVecAppend11",result, status);

	result = TestVecAppend12(&status);
	PrintResult("TestVecAppend12",result, status);

	result = TestVecAppend13(&status);
	PrintResult("TestVecAppend13",result, status);

	result = TestVecAppend14(&status);
	PrintResult("TestVecAppend14",result, status);

	result = TestVeDestroy11(&status);
	PrintResult("TestVeDestroy11",result, status);

	result = TestVecRemove12(&status);
	PrintResult("TestVecRemove12",result, status);
	
	



	return 0;
}
