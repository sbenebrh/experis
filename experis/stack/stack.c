#include"stack.h"
#include<stdlib.h>
#define EMPTY 1
#define NOT_EMPTY 0
/*TODO



*/



Stack* StackCreate(size_t _size, size_t _blockSize)
{
	Stack* newStack = NULL;

	if(_size == 0 && _blockSize == 0 )
	{
		return NULL;
	}

	newStack = (Stack*)malloc(sizeof(Stack));
	if(!newStack)
	{
		return NULL;
	}
	newStack -> vector = VectorCreate(_size, _blockSize);
	if(!newStack -> vector)
	{
		free(newStack);
		return NULL;
	}
	
	newStack -> s_magicNumber = MAGIC_NUMBER;

	return newStack;
}

void StackDestroy(Stack* _stack)
{
	if(!_stack || _stack -> s_magicNumber != MAGIC_NUMBER)
	{
		return;
	} 

	VectorDestroy(_stack -> vector);
	free(_stack);

	_stack -> s_magicNumber = NO_MAGIC_NUMBER;
	_stack = NULL;
}

ADTErr StackPush(Stack* _stack, int _item)
{

	if(!_stack )
	{
		return NOT_INITIALIZED;
	}
	if( _stack -> s_magicNumber != MAGIC_NUMBER)
	{
		return NOT_ORIGINAL_STACK;
	}
	return VectorAdd(_stack -> vector, _item);
}

ADTErr StackPop(Stack* _stack, int* _item)
{
	if(!_stack )
	{
		return NOT_INITIALIZED;
	}
	if( _stack -> s_magicNumber != MAGIC_NUMBER)
	{
		return NOT_ORIGINAL_STACK;
	}
	if(!StackIsEmpty(_stack))
		return VectorDelete(_stack -> vector, _item);
	return EMPTY_STACK;

}

ADTErr StackTop(Stack* _stack, int* _item)
{
	if(!_stack )
	{
		return NOT_INITIALIZED;
	}
	if( _stack -> s_magicNumber != MAGIC_NUMBER)
	{
		return NOT_ORIGINAL_STACK;
	}
	if(!StackIsEmpty(_stack))
		return VectorGet(_stack -> vector, _stack -> vector -> m_nitems -1 , _item );
	return EMPTY_STACK;
}

int StackIsEmpty(Stack* _stack)
{
	if(!_stack )
	{
		return NOT_INITIALIZED;
	}
	if( _stack -> s_magicNumber != MAGIC_NUMBER)
	{
		return NOT_ORIGINAL_STACK;
	}
	return _stack -> vector -> m_nitems ? EMPTY:NOT_EMPTY;

}

