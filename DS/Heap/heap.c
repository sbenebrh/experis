/*
 * heap.c
 * framework for heap
 * Version: 1.0
 * creation: 27/12/2018
 * last change: 30/12/2018
 * 		add comments
 *      Author: samuel ben ibgui   
 * 	    benebrhi@gmail.com
*/


#include<stdio.h>
#include<stdlib.h>
#include"heap.h"
#include"ADTErr.h"
#include"vector.h"
#define MAGICNUMBER 0XBEEFBEEF
#define CHECK_ALLOCATION(X) 	if(NULL == (X)) return ERR_UNINITIALIZED;
								

struct Heap
{
	size_t m_magicNumber;
	Vector* m_vec;
	size_t m_heapSize;
};
static void swap( int* _father, int* _son)
{	
	int temp = *_father;
	*_father = *_son;
	*_son = temp;
}

static void changeFather(Heap* _heap,int _index, int* _father, int _indexSon, int* _son)
{
	swap(_father, _son);
	VectorSet(_heap -> m_vec, _index,*_father);
	VectorSet(_heap -> m_vec, _indexSon, *_son);
}
static void Heapify(Heap* _heap, int _index)
{
	int father;
	int sonL, sonR;
	if(_index > _heap -> m_heapSize/2 -1)/*we reached a leaf*/
	{
		return;
	}
	VectorGet(_heap -> m_vec, _index, &father);
	VectorGet(_heap -> m_vec, _index* 2  + 1, &sonL);
	/*the father has only the son left but not the son right*/
	if(_index * 2 + 2 > _heap -> m_heapSize - 1)
	{
		if(father > sonL)
		{
			return;
		}
		else
		{

			changeFather(_heap, _index, &father, _index * 2 + 1 , &sonL);
			return;

		}
	}
	VectorGet(_heap -> m_vec, _index*2 + 2 , &sonR);

	if(father >sonL && father > sonR)
		return;

	else if(father > sonL && father < sonR)
	{	

		changeFather(_heap, _index, &father, _index * 2 + 2 , &sonR);
		Heapify(_heap, _index*2 + 2);
	}  
	else if(father < sonL && father > sonR)
	{	
		changeFather(_heap, _index, &father, _index * 2 + 1 , &sonL);
		Heapify(_heap, _index*2 + 1);
	} 
	else if(father < sonL && father < sonR)
	{
		if(sonL > sonR)
		{
			changeFather(_heap, _index, &father, _index * 2 + 1 , &sonL);
			Heapify(_heap, _index*2 + 1);
		}
		else
		{
			changeFather(_heap, _index, &father, _index * 2 + 2 , &sonR);
			Heapify(_heap, _index*2 + 2);
		}
	}
}

static void fixHeap(Heap* _heap)
{
	int i ;
	
	for(i = _heap -> m_heapSize/2 - 1; i >= 0 ; i--)
	{
		Heapify(_heap, i);
	}
}

static void HeapInsertUp(Heap* _heap , int _size)
{
	int father;
	int son;
	if(_size <= 1)
	{
		return ;
	}
	VectorGet(_heap -> m_vec, _size/ 2  - 1, &father);
	VectorGet(_heap -> m_vec, _size - 1 , &son);

	if(father >= son)
	{
		return ;
	}
	swap(&father, &son);
	VectorSet(_heap -> m_vec, _size/2 - 1, father);
	VectorSet(_heap -> m_vec, _size - 1 , son);

	HeapInsertUp(_heap , _size / 2);

}


static void initializeHeap(Heap* _heap, Vector* _vec)
{
	int size;

	_heap -> m_magicNumber = MAGICNUMBER;
	_heap -> m_vec = _vec;

	VectorItemsNum(_heap -> m_vec, &size);
	_heap -> m_heapSize = size;
}

Heap* HeapBuild(Vector* _vec)
{	
	
	Heap* newHeap;
	if(NULL == _vec)
	{
		return NULL;
	}

	newHeap = (Heap*) malloc(sizeof(Heap));
	if(NULL == newHeap)
	{
		return NULL;
	}
	
	initializeHeap(newHeap, _vec); 

	fixHeap(newHeap); /* from the size/2 element to the beginning  do heapify*/

	return newHeap;

}


void HeapDestroy(Heap* _heap)
{
	if(NULL != _heap && _heap -> m_magicNumber == MAGICNUMBER)
	{
		free(_heap);
		_heap ->m_magicNumber = 0;
	}
}

ADTErr HeapInsert(Heap* _heap, int _data)
{
	CHECK_ALLOCATION(_heap)

	_heap -> m_heapSize += 1;

	if(VectorAdd(_heap -> m_vec, _data) != ERR_OK)
	{
		return ERR_ADD_MISS;
	}
	HeapInsertUp(_heap, _heap -> m_heapSize  );

	return ERR_OK;

}

ADTErr HeapMax(Heap* _heap, int* _data)
{
	CHECK_ALLOCATION(_heap);

	return VectorGet(_heap -> m_vec, 0 , _data);
}


ADTErr HeapExtractMax(Heap* _heap, int* _data)
{
	int max;
	int last;
	ADTErr status;
	CHECK_ALLOCATION(_heap)
	if(_heap -> m_heapSize == 0)
	{
		return ERR_EMPTY;
	}
	
	status |= VectorGet(_heap -> m_vec, _heap -> m_heapSize - 1, &last);
	status |= VectorGet(_heap -> m_vec, 0 , &max);

	*_data = max;

	swap(&max, &last);

	status |= VectorSet(_heap -> m_vec, 0 , max);
	status |= VectorDelete(_heap -> m_vec, &max);
	_heap -> m_heapSize--;
	Heapify( _heap, 0);

	return status;
}


int HeapItemsNum(Heap* _heap)
{
	CHECK_ALLOCATION(_heap);

	return _heap -> m_heapSize;
}


void HeapItemsPrint(Heap* _heap)
{
	if(_heap)
	{
		VectorPrint(_heap -> m_vec);
		printf("\n");
	}
	
}
