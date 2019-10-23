#include<stdlib.h>
#include"vector.h"





ADTErr checkSegmentationError(void* _ptr)
{
	if(! _ptr)
		return ERR_SEGMENTATION;
	return ERR_OK;
}

ADTErr checkErrInput(int value, int limit)
{
	if(value < limit)
		return ERR_INPUT;
	return ERR_OK;
}

void initializeVector(Vector* _vector,size_t  _initialSize,size_t _extensionBblockSize)
{
	_vector -> m_nitems = 0;
	_vector -> m_size = _initialSize;
	_vector -> m_originalSize = _initialSize;
	_vector -> m_blockSize = _extensionBblockSize;
	_vector -> m_items = (int*)malloc(_initialSize * sizeof(int));
}

ADTErr reSize(Vector*_vector,int _increaseBlocksfactor)
{
	int * temp = (int*) realloc(_vector -> m_items,(_vector -> m_size +(_vector -> m_blockSize * _increaseBlocksfactor ))  * sizeof(int));
	if(temp)
	{
		_vector -> m_items = temp;
		_vector -> m_size += _vector -> m_blockSize * _increaseBlocksfactor;
		return ERR_OK;
	}
	return ERR_REALLOCATION;
}

 void insertItem(Vector* _vector,int _item)
 {
 	_vector -> m_items[_vector -> m_nitems] = _item;
 	_vector -> m_nitems += 1;
 }

 int findIndex(Vector* _vector, int _number)
 {
 	int i ;
 	for( i = 0; i < _vector -> m_nitems; i++)
 	{
 		if(_vector -> m_items[i] == _number)
 			return i;
 	}
 	return -1;
 }
 void shiftLeft(Vector* _vector,int index)
 {
 	int i = index;
 	for(;i < _vector -> m_nitems - 1;i++)
 		_vector -> m_items[i] = _vector -> m_items[i + 1];
 }

void VectorPrint(Vector* _vector){
	int i;
	if(checkSegmentationError(_vector) != ERR_OK || checkSegmentationError(_vector -> m_items) != ERR_OK){
		return;
	}
	for(i = 0; i < _vector -> m_nitems; i++)
	{
		printf("%d\t",_vector -> m_items[i]);
	}
}

Vector* VectorCreate(size_t _initialSize, size_t _extensionBblockSize)
{
	Vector* FirstVector = NULL;

	if(checkErrInput(_initialSize,1) == ERR_INPUT && checkErrInput(_extensionBblockSize,1) == ERR_INPUT)
	{
		return NULL;
	}

	FirstVector = (Vector*) malloc( sizeof(Vector));
	if(checkSegmentationError((void*) FirstVector) == ERR_ALLOCATION)
	{
		return NULL;
	}

	initializeVector(FirstVector, _initialSize, _extensionBblockSize);
	if(checkSegmentationError(FirstVector) == ERR_SEGMENTATION)
	{
		free(FirstVector);
		return NULL;
	}

	return FirstVector;

}

void VectorDestroy(Vector* _vector)
{
	if(_vector)
		if(_vector -> m_items)
			free(_vector);
}

ADTErr VectorAdd(Vector* _vector, int _item)
{

	if(checkSegmentationError(_vector) != ERR_OK || checkSegmentationError(_vector -> m_items) != ERR_OK)
	{
		return ERR_SEGMENTATION;
	}

	if(_vector ->m_size == _vector -> m_nitems && _vector -> m_blockSize == 0)
	{
		return ERR_OVER_MAX_BLOCKS;
	}

	if(_vector ->m_size == _vector -> m_nitems && _vector -> m_blockSize > 0)
	{
		if(reSize(_vector,1.3) == ERR_REALLOCATION)
		{
			return ERR_REALLOCATION;
		}
	}

	insertItem(_vector, _item);

	return ERR_OK;

}

ADTErr VectorDelete(Vector* _vector, int* _item)
{

	if(checkSegmentationError(_vector) != ERR_OK || checkSegmentationError(_vector -> m_items) != ERR_OK)
	{
		return ERR_SEGMENTATION;
	}

	*_item = _vector ->m_items[_vector -> m_nitems - 1];
	_vector -> m_nitems -= 1;

	if(_vector -> m_size - _vector -> m_nitems > 2* _vector -> m_blockSize && _vector -> m_size > _vector -> m_originalSize )
	{	
		if(reSize(_vector, -1) == ERR_REALLOCATION)
		{
			return ERR_REALLOCATION;
		}
	}

	return ERR_OK;
}
ADTErr VectorGet(Vector* _vector, size_t _index, int * item)
{
	if(checkSegmentationError(_vector) != ERR_OK)
	{
		return ERR_UNINITIALIZED;
	}
	*item = _vector -> m_items[_index] ;
	return ERR_OK;
}

ADTErr VectorSet(Vector* _vector, size_t _index, int  _item)
{
	if(checkSegmentationError(_vector) != ERR_OK)
	{
		return ERR_UNINITIALIZED;
	}
	
        _vector->m_items[_index] = _item;
    return ERR_OK;
}

ADTErr VectorItemsNum(Vector* _vector, int* _numOfItems)
{
	if(checkSegmentationError(_vector) != ERR_OK )
	{
		return ERR_SEGMENTATION;
	}

	*_numOfItems = _vector ->m_nitems;
	return ERR_OK;
}

