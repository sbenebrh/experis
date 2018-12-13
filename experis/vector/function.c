#include<stdlib.h>
#include"function.h"





ADTErr checkSegmentationError(void* _ptr)
{
	if(! _ptr)
		return ERR_SEGMENTATION;
	return ERR_WELL;
}

ADTErr checkErrInput(int value, int limit)
{
	if(value < limit)
		return ERR_INPUT;
	return ERR_WELL;
}

void initializeVector(Vector* _vector,size_t  _initialSize,size_t _extensionBblockSize)
{
	_vector -> m_nitems = 0;
	_vector -> m_size = _initialSize;
	_vector -> m_originalSize = _initialSize;
	_vector -> m_blockSize = _extensionBblockSize;
	_vector -> m_items = (int*)calloc(_initialSize , sizeof(int));
}

ADTErr reSize(Vector*_vector,int _increaseBlocks)
{
	int * temp = (int*) realloc(_vector -> m_items,(_vector -> m_size + _increaseBlocks) * sizeof(int));
	if(temp)
	{
		_vector -> m_items = temp;
		_vector -> m_size += _increaseBlocks;
		return ERR_WELL;
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
	if(checkSegmentationError(_vector) != ERR_WELL || checkSegmentationError(_vector -> m_items) != ERR_WELL){
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

	FirstVector = (Vector*) malloc(_initialSize * sizeof(Vector));
	if(checkSegmentationError((void*) FirstVector) == ERR_ALLOCATION)
	{
		return NULL;
	}

	initializeVector(FirstVector, _initialSize, _extensionBblockSize);
	if(checkSegmentationError(FirstVector) == ERR_SEGMENTATION)
	{
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

	if(checkSegmentationError(_vector) != ERR_WELL || checkSegmentationError(_vector -> m_items) != ERR_WELL)
	{
		return ERR_SEGMENTATION;
	}

	if(_vector ->m_size == _vector -> m_nitems && _vector -> m_blockSize == 0)
	{
		return ERR_OVER_MAX_BLOCKS;
	}

	if(_vector ->m_size == _vector -> m_nitems && _vector -> m_blockSize > 0)
	{
		if(reSize(_vector,_vector -> m_blockSize) == ERR_REALLOCATION)
		{
			return ERR_REALLOCATION;
		}
	}

	insertItem(_vector, _item);

	return ERR_WELL;

}

ADTErr VectorDelete(Vector* _vector, int* _item)
{
	int index;

	if(checkSegmentationError(_vector) != ERR_WELL || checkSegmentationError(_vector -> m_items) != ERR_WELL)
	{
		return ERR_SEGMENTATION;
	}

	index = findIndex(_vector, *_item);
	if(0 > index)
	{
		return ERR_NOT_IN_VECTOR;
	}

	*_item = _vector ->m_items[index];
	shiftLeft(_vector, index);
	_vector -> m_nitems -= 1;
	if(_vector -> m_size - _vector -> m_nitems > 1 && _vector -> m_size > _vector -> m_originalSize )
	{	
		if(reSize(_vector, -1) == ERR_REALLOCATION)
		{
			return ERR_REALLOCATION;
		}
	}

	return ERR_WELL;
}
ADTErr VectorGet(Vector* _vector, size_t _index, int * item)
{
	if(checkSegmentationError(_vector) != ERR_WELL || checkSegmentationError(_vector -> m_items) != ERR_WELL)
	{
		return ERR_SEGMENTATION;
	}
	*item = _vector -> m_items[_index] ;
	return ERR_WELL;
}

ADTErr VectorSet(Vector* _vector, size_t _index, int  _item)
{
	if(checkSegmentationError(_vector) != ERR_WELL)
		return 
		 ERR_SEGMENTATION;

	if (_index < _vector->m_nitems)
        _vector->m_items[_index] = _item;
    return ERR_WELL;
}

ADTErr VectorItemsNum(Vector* _vector, int* _numOfItems)
{
	if(checkSegmentationError(_vector) != ERR_WELL )
	{
		return ERR_SEGMENTATION;
	}

	*_numOfItems = _vector ->m_nitems;
	return ERR_WELL;
}

