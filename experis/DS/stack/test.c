#include<math.h>
#include"stack.h"


typedef enum statusErr {
	SUCCEED,
	FAIL,
	ERROR
}TestResult;
void PrintResult(char* _testName, TestResult _result, ADTErr _stat)
{
	if(_stat != ERR_WELL) printf("%s %s \n","test error of the", _testName );
	printf("%s\t%s\n",_testName, (_result == SUCCEED)? "succed": "failed" );
}
/*
*@brief create pointer to stack and check if it create it propely
*
* @return the status of the test
**/

TestResult TestStackCreate1(ADTErr* _status)
{
	Stack* stack;
	
	TestResult  result = FAIL;
	stack = StackCreate(5,2);
	if (stack )
	{	
		StackDestroy(stack);
		stack = StackCreate(0,5);
		if(stack)
		{
			StackDestroy(stack);
			stack = StackCreate(6,0);
		
			if (stack)
			{
				result = SUCCEED;
				*_status = ERR_WELL; 
				StackDestroy(stack);
			}
		}
		
	}
	return result;
		
}
TestResult TestStackCreate2(ADTErr* _status)/*check the boundary of the system*/
{
		Stack* stack = StackCreate(pow(2,500),0);

		return stack == NULL ? SUCCEED:FAIL ;
}

TestResult TestStackCreate3(ADTErr* _status)/*check if the created stack is able to contain element*/
{
	int topnumber;
	Stack* stack = StackCreate(5,0);
	*_status = StackPush(stack, 10);
	*_status |= StackTop(stack, &topnumber);
	StackDestroy(stack);
	if(*_status)
	{
		if(topnumber != 10)
		return FAIL;
}
	return *_status != ERR_WELL ? ERROR: SUCCEED;


}

/* check if when i create a stack i get nothing at its top*/

TestResult TestStackCreate4(ADTErr* _status)
{
	int topnumber;
	Stack* stack = StackCreate(5,0);
	*_status = StackTop(stack, &topnumber);
	StackDestroy(stack);

	return (*_status != ERR_WELL && topnumber) ? FAIL: SUCCEED;

}

/*check when i destroy a stack twice it doesn t work*/
TestResult TestStackDestroy1(ADTErr* _status)
{
	Stack * stack = StackCreate(9, 1);
	StackDestroy(stack);
	StackDestroy(stack);

	*_status = ERR_WELL;
	return SUCCEED;
}

TestResult TestStackDestroy2(ADTErr* _status)
{
	Stack * stack = StackCreate(9, 1);
	StackDestroy(stack);
	if(StackIsEmpty(stack) == 1)
		*_status = ERR_WELL;
	return SUCCEED;
}
/* check if the stack is able to contains items and the reallocation*/
TestResult TestStackPush1(ADTErr* _status)
{
	int topnumber;
	Stack * stack = StackCreate(1, 1);
	 *_status = StackPush(stack, 10);
	 *_status |= StackPush(stack, 11);
	 *_status |= StackTop(stack, &topnumber);
	 StackDestroy(stack);
	 if(*_status == ERR_WELL) return topnumber == 11 ? SUCCEED : FAIL;
	 return ERROR;

}
/*check if i create more than 1 pointer to the stack there is no merge */
TestResult TestStackPush2(ADTErr* _status)
{
	int topnumber1, topnumber2;
	Stack * stack1 = NULL;
	Stack * stack2 = NULL;

	stack1 = StackCreate(3, 4);
	stack2 = StackCreate(2, 0);

	*_status = StackPush(stack1, 13);
	*_status |= StackPush(stack2, 14);

	*_status |= StackTop(stack1, &topnumber1);
	*_status |= StackTop(stack2, &topnumber2);

	StackDestroy(stack1);
	StackDestroy(stack2);

	if(*_status == ERR_WELL) return topnumber1 == topnumber2 ? FAIL: SUCCEED;
	 return ERROR;
}
/*check if the function pop element from the stack*/
TestResult TestStackPop1(ADTErr* _status)
{
	int number;
	Stack * stack = StackCreate(9, 1);
	*_status = StackPush(stack, 13);
	*_status |= StackPop(stack, &number);
	if (*_status ==ERR_WELL )
		return StackIsEmpty(stack) == 1 ? SUCCEED: FAIL;
	return ERROR;

}

int main()
{

	TestResult result ;
	ADTErr status ;
	result = TestStackCreate1(&status);
	PrintResult("TestStackCreate1", result,status);

	result = TestStackCreate2(&status);
	PrintResult("TestStackCreate2", result,status);

	result = TestStackCreate3(&status);
	PrintResult("TestStackCreate3", result,status);

	result = TestStackCreate4(&status);
	PrintResult("TestStackCreate4", result,status);

		result = TestStackDestroy1(&status);
	PrintResult("TestStackDestroy1", result,status);
		result = TestStackDestroy2(&status);
	PrintResult("TestStackDestroy2", result,status);


		result = TestStackPush1(&status);
	PrintResult("TestStackPush1", result,status);


		result = TestStackPop1(&status);
	PrintResult("TestStackPop1", result,status);

		result = TestStackPush2(&status);
	PrintResult("TestStackPush2", result,status);
	return 0;
}
