#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"stack.h"
#include"ADTErr.h"


int checkorder(char _action, char _nextaction)
{
	if(_action == '+' || _action == '-')
	{
		return 1;
	}
	if(_nextaction == '+' || _nextaction == '-')
	{
		return 0;
	}
	return 1;
}

ADTErr checkExpression(char* _expression, char* _result)
{
	int i, top,arrayPos = 0;
	int popped, temp, flag = 0;
	int length = strlen(_expression);
	ADTErr status;
	Stack* bracketStack = StackCreate(length/2, length/2);
	if(!bracketStack)
	{
		return ERR_ALLOCATION;
	}
	for(i = 0;i < length; i++)
	{
		switch(_expression[i])
		{
			case '(':

				StackPush(bracketStack, (int) _expression[i]);
			break;

			case ')':
				StackTop(bracketStack,&top);
				while(top != '(' )
				{
					if(StackIsEmpty(bracketStack))
					{
						break;
					}
					StackPop(bracketStack, &popped);
					_result[arrayPos] = popped;
					i++;
					arrayPos++;
					StackTop(bracketStack,&top);
				}
				StackPop(bracketStack, &popped);

				i--;

				break;

			case '+':
			case '-':
			case '*':
			case '/':
				temp = _expression[i];
				StackTop(bracketStack,&top);
				while(checkorder(_expression[i], top) && top != '(' && !				  StackIsEmpty(bracketStack))
				{
					flag = 1;
					StackPop(bracketStack, &popped);
					_result[arrayPos] = popped;
					i++;
					arrayPos++;
					StackTop(bracketStack,&top);
				}
				if(flag)
				{
					i--;
					flag = 0;
				}
				StackPush(bracketStack, temp);
				break;
			default:
			if(isdigit(_expression[i]))
			{
				_result[arrayPos] = _expression[i];
				arrayPos++;
			}
			break;
		}
	}
	while(!StackIsEmpty(bracketStack))
	{
		StackPop(bracketStack, &popped);
		_result[arrayPos] = popped;
		arrayPos ++;
	}

	

	StackDestroy(bracketStack);
	return ERR_OK;
	
}

int resolvePostfixOperation(char* _postfixArr)
{
	int result;
	int i;
	int popped1, popped2;
	int length = strlen(_postfixArr);
	Stack* bracketStack = StackCreate(length/2, length/2);
	for(i = 0; i< length; i++)
	{
		if(isdigit(_postfixArr[i]))
		{
			StackPush(bracketStack, _postfixArr[i]);
		}
		else
		{
			StackPop(bracketStack, &popped1);
			StackPop(bracketStack, &popped2);
			switch(_postfixArr[i])
			{
				case '+':
					result = (popped1 - '0') + (popped2- '0');
					break;
				case '-':
					result = (popped1 - '0') - (popped2- '0');
					break;
				case '*':
					result = (popped1 - '0') * (popped2 - '0');
					break;
				case '/':
					result = (popped1 - '0') / (popped2 - '0');
					break;
			}
			StackPush(bracketStack, result);	
		}
	}
	StackPop(bracketStack, &result);
	return result;

}
int main()
{
	char expression[128];
	char* postfix;
	ADTErr status;

	printf("please enter an expression of brackets\n");
	scanf("%s",expression );
	postfix = (char*) malloc(strlen(expression) * sizeof(char));

	if(status = checkExpression(expression, postfix) != ERR_OK)
	{
		printf("%s %d\n","not correspondBrack",status );
		return status;
	}
	printf("%s %s\n", "well done this is the postfix expression", postfix );
	printf("%s %d", "the result is: ", resolvePostfixOperation(postfix));

	return 0;
	

}
