#include"../vector/function.h"
#define MAGIC_NUMBER 0XBEEFBEEF
#define NO_MAGIC_NUMBER 0XDEADBEEF

typedef struct stack
{
	unsigned int s_magicNumber;
	Vector* vector;
}Stack;

Stack* StackCreate(size_t _size, size_t _blockSize);/*done*/
void StackDestroy(Stack* _stack);/*done*/
ADTErr StackPush(Stack* _stack, int _item);/*done*/
ADTErr StackPop(Stack* _stack, int* _item);/*done*/
ADTErr StackTop(Stack* _stack, int* _item);/*done*/
int StackIsEmpty(Stack* _stack);


void StackPrint(Stack* _stack);