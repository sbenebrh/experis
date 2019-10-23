#include<stdio.h>
#include<string.h>
#include"stack.h"
#include"ADTErr.h"


int correspondBrack(char _enter, char _exit)
{
	switch (_enter)
	{
		case ')':
			return !_exit =='(';
		case '}':
			return !_exit =='{';	
		case ']':
			return !_exit =='[';
	}
}




ADTErr checkBracket(Stack * _stack, char _brack)
{
	int brackfirst;
	ADTErr status;
	switch(_brack)
	{
		case '(':
		case '{':
		case '[':
			StackPush(_stack,(int)_brack); /*check if casting work*/
			break;
		case ')':
		case '}':
		case ']':
			if(status = StackPop(_stack, &brackfirst) != ERR_WELL)
			{
				return status;
			}
			return correspondBrack(_brack, brackfirst) ;

	}
	return ERR_OK;
}



ADTErr checkExpression(char* _expression)
{
	int i;
	int length = strlen(_expression);
	ADTErr status;
	Stack* bracketStack = StackCreate(length/2, length/2);
	if(!bracketStack)
	{
		return ERR_ALLOCATION;
	}
	for(i = 0;i < length; i++)
	{
		if((status = checkBracket(bracketStack, _expression[i])) != ERR_OK)
		{
			StackDestroy(bracketStack);
			return status;
		}
	}

	if(StackIsEmpty(bracketStack))
	{
		StackDestroy(bracketStack);
		return ERR_OK;
	}
	StackDestroy(bracketStack);
	return ERR_NOT_EMPTY;
}


int main()
{
	char expression[128];
	ADTErr status;

	printf("please enter an expression of brackets\n");
	scanf("%s",expression );

	if(status = checkExpression(expression) != ERR_OK)
	{
		printf("%s %d\n","not correspondBrack",status );
		return status;
	}
	printf("%s\n", "well done" );

	return 0;
	

}