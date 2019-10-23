#include<stdlib.h>
#include <string.h>
#include"sorts.h"
#include "vector.h"
#include "ADTErr.h"
#include "stack.h"

#define IS_SWAPPED 0

#define CHECKPOINTER(X)		if(NULL == (X))	return ERR_UNINITIALIZED;
	

/*################STATIC FUNCTIONS########################*/
static int bubbleUp(Vector* _vec,int _begin ,int _size,int (*f)(int,int));
static void swapByIndex(Vector* _vec, int _index1, int _index2);
static int sortUp(void* _elements,size_t _elementSize,size_t _size,int(*_less)(const void*, const void*),char* _tmpArr );
static void swapGeneric(void* element1,void* element2,size_t _elementSize, char* _tmpArr);
/*########################################################*/


ADTErr BubbleSort(Vector* _vec,int (*f)(int,int))
{
	int i = 0;
	int nItems;
	ADTErr status;

	CHECKPOINTER(_vec);

	status = VectorItemsNum(_vec, &nItems);
	if( 0== nItems)
	{
		return ERR_EMPTY;
	}

	if(1 == nItems)
	{
		return ERR_OK;
	}
	for(i = 0; i < nItems ; i++)
	{
		if(IS_SWAPPED == bubbleUp(_vec, 0,nItems - i - 1,f) )
		{
			break;
		}

	}
	return status;


}

int sort(void* _elements, size_t _elementSize, size_t _size, int(*_less)(const void*, const void*))
{
	int i;
	char* tmpArr = (char*)malloc((_elementSize + 1) * sizeof(char));

	CHECKPOINTER(_elements);
	
	for(i = 0; i < _size ; i++)
	{
		if(sortUp(_elements, _elementSize,_size - i - 1,_less,tmpArr) == IS_SWAPPED)
		{
			break;
		}

	}
	free(tmpArr);
	return ERR_OK;
}


/*########################STATIC FUNCTIONS##############################*/

/*this bubble implementation works for both ways*/
static int bubbleUp(Vector* _vec,int _begin ,int _size,int (*f)(int,int))
{
	int i = 0, isSwapped = 0;
	int item1, item2;

	for(i = _begin; i < _size ; ++i)
	{
		VectorGet(_vec, i, &item1);
		VectorGet(_vec, i + 1, &item2);

		if((*f)(item1, item2) == 1)
		{
			VectorSet(_vec, i, item2);
			VectorSet(_vec, i + 1, item1);

			isSwapped = 1;
		}
	}
	return isSwapped;


}




static void swapByIndex(Vector* _vec, int _index1, int _index2)
{
	int first, second;

	VectorGet(_vec, _index1, &first);
	VectorGet(_vec, _index2, &second);

	VectorSet(_vec,_index1, second);
	VectorSet(_vec, _index2, first);
}

static int sortUp(void* _elements,size_t _elementSize,size_t _size,int(*_less)(const void*, const void*),char* _tmpArr )
{
	int i;
	void *element1, *element2;
	int isSwapped = 0;
	for(i = 0; i <= _size; ++i)
	{
		element1 = ((char*)_elements + i * _elementSize);
		element2 = ((char*)_elements + (i + 1) * _elementSize);

		if(((*_less)(element1,element2)) == 1)
		{
			isSwapped = 1;
			swapGeneric(element1,element2,_elementSize, _tmpArr);
		}
	}
	return isSwapped;
}

static void swapGeneric(void* _element1, void* _element2, size_t _elementSize, char* _tmpArr)
{
	memcpy((void*)_tmpArr, _element1, _elementSize );
	memcpy(_element1, _element2,_elementSize );
	memcpy(_element2,(void*)_tmpArr, _elementSize );
}