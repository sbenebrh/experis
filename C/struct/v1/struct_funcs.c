#include"struct_funcs.h"

int * Dcreate(int _size, int * _numOfElement)
{

	if(_size < 0 ||  ! _numOfElement ){return NULL;}

	if(! _numOfElement)
	{
		*_numOfElement = 0;
	}

	return (int*)malloc( _size * sizeof(int));
}

void Ddestroy(int * _ptr)
{
	if(_ptr)
	{
		free(_ptr);
	}
}
void print(int * _arr, int _numberOfElement)
{	
	if(_arr && _numOfElement > 0)
	{
		int i;
		for(i = 0; i < _numberOfElement; i++)
		{
			printf("%d ", _arr[i]);
		}
		printf(" \n");
	}
}


int Dadd(int ** _arr, int _data, int * _size, int * _numOfElement, int _increaseBlock)
{	/* TODO  check NULL for Pointers*/
	int * temp = NULL;
	if( !_arr ||! _size || ! _numOfElement || ! *_arr)
	{
		return SEGMENTATION_FAULT;
	}

	if(*_size < 0 || *_numOfElement < 0 || _increaseBlock < 0)
	{
		return ERR_INPUT;
	}

	if(*_size == *_numOfElement && _increaseBlock > 0)
	{
		temp = realloc(*_arr, (*_size + _increaseBlock) * sizeof(int));

		if (temp != NULL)
		{
			*_arr = temp;
		}
		else
		{
			return SEGMENTATION_FAULT;
		}
	}
	else if (*_size == *_numOfElement && _increaseBlock == 0)
	{
		return ERR_INCREASE;
	}

	*(*_arr + * _numOfElement) = _data;
	*_numOfElement += 1;
		
	
	return 1;
}	
int Dremove(int * _arr, int * _data, int _size, int * _numOfElement)
{
	if( !_arr || !_data || !_numOfElement)
	{
		return SEGMENTATION_FAULT;
	}

	if(! *_numOfElement)
	{
		return ERR_UNDERFLOW;
	}

	*_data = _arr[*_numOfElement-1];
	*_numOfElement -= 1;

	return *_data;
}
