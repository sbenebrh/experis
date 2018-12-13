#include"stack.h"


typedef statusErr {
	PASS,
	FAIL,
	ERROR
}statusErr;

void TestStackCreate()
{
	stack * stack;
	statusErr  status = PASS;
	stack = StackCreate(5,2);
	if (!stack )
		status = FAIL;
	StackDestroy(stack);
	stack = StackCreate(0,5);
	

}

int main()
{
	return 0;
}