#include"stack.h"
#include<stdlib.h>
#define EMPTY 1
#define NOT_EMPTY 0

typedef struct Vector Stack;


Stack* StackCreate(size_t _size, size_t _blockSize)
{
	return VectorCreate(_size, _blockSize) ;
}

void StackDestroy(Stack* _stack)
{
	
	VectorDestroy(_stack);
}

ADTErr StackPush(Stack* _stack, int _item)
{

	return VectorAdd(_stack, _item);
}

ADTErr StackPop(Stack* _stack, int* _item)
{
	return VectorDelete( _stack, _item);
}

ADTErr StackTop(Stack* _stack, int* _item)
{
	int index ;
	VectorItemsNum( _stack, &index);
	return VectorGet( _stack, index -1 , _item );
}

int StackIsEmpty(Stack* _stack)
{
	int index ;
	VectorItemsNum( _stack, &index);
	return !index ? EMPTY:NOT_EMPTY;

}

