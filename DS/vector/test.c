#include"vector.h"
enum statusTest {
	PASS,
	FAIL,
	ERROR
};

void printStatusTest(char* _testName,char * _status)
{
	printf("the %s %s\n",_testName, _status);
}

void GetPostiveTest()
{
	 ADTerr status;
	 int returnNumber;
	 enum statusTest;
	 Vector * controler = VectorCreate(10, 2);
	 status = VectorAdd(controler, 15);

	 if(status == ERR_WELL)
	 {
	 	status = VectorGet(controler, 0, &returnNumber);
	 	if(status == ERR_WELL && returnNumber == 15)
	 	{

	 		printStatusTest("GetPostiveTest", "PASS");
	 	}
	 	else
	 		printStatusTest("GetPostiveTest" , "FAIL");
	 }
	 else
	 	printStatusTest("GetPostiveTest" , "ERROR");
	 VectorDestroy(controler);

}
void SetPostiveTest()
{
	ADTerr status;
	 int returnNumber = 9;
	 enum statusTest;
	 Vector * controler = VectorCreate(10, 2);
	 status = VectorAdd(controler, 15);

	 if(status == ERR_WELL)
	 {
	 	status = VectorSet(controler, 0, returnNumber );
	 	if(status == ERR_WELL)
	 	{
	 		status = VectorGet(controler, 0, &returnNumber);
	 		if(returnNumber == 9)
	 			printStatusTest("SetPostiveTest", "PASS");
	 		else 
	 			printStatusTest("SetPostiveTest", "FAIL");
	 		
	 	}
	 	
	 }
	 else
	 	printStatusTest("SetPostiveTest" , "ERROR");



}

int main()
{
	GetPostiveTest();
	SetPostiveTest();
}
