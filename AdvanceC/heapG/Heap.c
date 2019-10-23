#include "Heap.h"
#include "vector.h"

#define LEFT_SON_IND(i) (2*(i)+1)
#define RIGHT_SON_IND(i) (2*(i)+2)



struct Heap
{
	Vector* m_vec;
	int m_size;
	LessThanComparator m_compFunc;
};


/*static utility functions*/
/*sift element up the heap, called by Heap_Insert*/
static void HeapSiftUp(Heap* _heap, size_t i);


/*TODO
 heapify should look like:
 	FindMaxOf3(father,left,right)
 	if father is not max
 		Swap(father,max)
 	heapify(max index)
	MODULARITY! this is easy to read ,and to debug!
*/


/*heapify recursively*/
static void HeapifyRec(Heap* _heap,int i)
{
	int left,right,max;
	void* iElem;
	void* maxElem;
	void* leftElem;
	void* rightElem;

	/*assume index i holds the max already*/
	max=i;
	left=2*i+1;
	right=2*i+2;

	/*the number to check is outside vector bounds*/
	if (i > _heap->m_size -1)
	{
		return;
	}

	/*the index i checked is a leaf, no action required*/
	if (left > _heap->m_size-1 && right > _heap->m_size-1)
	{
		return;
	}

	Vector_Get(_heap->m_vec, left, &leftElem); 	
	Vector_Get(_heap->m_vec, i, &maxElem);
	/*i is smaller than left child*/
	if( left <= _heap->m_size-1 && (*_heap->m_compFunc)(maxElem,leftElem) == TRUE )
	{
		max=left;
	}

	Vector_Get(_heap->m_vec, right, &rightElem); 	
	Vector_Get(_heap->m_vec, max, &maxElem);
	/*right child is bigger than the current max*/
	if (right <= _heap->m_size-1 && (*_heap->m_compFunc)(maxElem,rightElem) == TRUE )
	{
		max=right;
	}

	/*need to swap and heapify only if i is not max*/
	if(max != i)
	{
		/*swap between i and max*/
		Vector_Get(_heap->m_vec, i, &iElem); 	
		Vector_Get(_heap->m_vec, max, &maxElem);
		Vector_Set(_heap->m_vec, i, maxElem);
		Vector_Set(_heap->m_vec, max, iElem);
		/*heapify the index that now might viloate the heap property*/
		HeapifyRec(_heap,max);
	}
}


/*build heap from a given vector*/
Heap* Heap_Build(Vector* _vec, LessThanComparator _pfLess)
{
	int i;
	Heap* heap;

	if (!_vec || !_pfLess)
	{
		return NULL;
	}

	heap=(Heap*) malloc(sizeof(Heap));
	if (!heap)
	{
		return NULL;
	}
	heap->m_vec=_vec;
	heap->m_size=Vector_Size(_vec);
	heap->m_compFunc=_pfLess;

	/*heapify the heap*/
	i=(heap->m_size/2)-1;
	for(; i >= 0; i--)
	{
		HeapifyRec(heap,i);
	}
	return heap;
}


/*destroy heap*/
Vector* Heap_Destroy(Heap** _heap)
{
	Vector* vec;

	if(!_heap || !*_heap)
	{
		return NULL;
	}
	
	vec=(*_heap)->m_vec;
	free(*_heap);
	*_heap=NULL;
	return vec;	
}



/*insert an element to the heap*/
Heap_Result Heap_Insert(Heap* _heap, void* _element)
{
	Vector_Result appendRes;

	if(!_heap || !_element)
	{
		return HEAP_NOT_INITIALIZED;
	}

	if(!_element)
	{
		return HEAP_ELEM_NULL;
	}

	appendRes=Vector_Append(_heap->m_vec,_element);
	if(appendRes == VECTOR_ALLOCATION_ERROR)
	{
		return HEAP_REALLOCATION_FAILED;
	}	
	
	if(appendRes == VECTOR_FULL)
	{
		return HEAP_FULL;
	}

	_heap->m_size++;
	
	/*new number added at the end of the vector, need to sift it up to the correct position*/
	HeapSiftUp(_heap,_heap->m_size-1);

	return HEAP_SUCCESS;
}


/*sift element up, utility function called by Heap_Insert*/
static void HeapSiftUp(Heap* _heap, size_t i)
{
	int parent;
	void* iElem;
	void* parentElem;

	if(i == 0)
	{
		return;
	}

	parent=(i-1)/2;

	Vector_Get(_heap->m_vec, i, &iElem); 	
	Vector_Get(_heap->m_vec, parent, &parentElem);
	/*if parent is bigger then i, need to sift i up*/
	if (_heap->m_compFunc(parentElem,iElem) == TRUE)
	{
		Vector_Set(_heap->m_vec, i, parentElem);
		Vector_Set(_heap->m_vec, parent, iElem);
		HeapSiftUp(_heap, parent);
	}
}



/*perform an action on each heap element*/
size_t Heap_ForEach(const Heap* _heap, ActionFunction _action, void* _context)
{
	size_t i,nElem;
	void* element;

	if(!_heap || !_action)
	{
		return 0;
	}

	nElem=Heap_Size(_heap); 

	for(i=0; i < nElem ; ++i)
 	{
       	 Vector_Get(_heap->m_vec,i,&element);
         if(_action(element,_context) == 0)
		 {
			break;
		 }	
  	}
 	return i;
}


/*get item at the top of the heap, without removing it*/
const void* Heap_Peek(const Heap* _heap)
{
	void* elem;

	if(!_heap || Heap_Size(_heap) == 0)
	{
		return NULL;
	}

	Vector_Get(_heap->m_vec,0,&elem);
	return elem;
}


/*get item at the top of the heap and remove it*/
void* Heap_Extract(Heap* _heap)
{
	void* max;
	void* lastElem;

	if(!_heap || Heap_Size(_heap) == 0)
	{
		return NULL;
	}

	Vector_Get(_heap->m_vec,0,&max);
	Vector_Remove(_heap->m_vec,&lastElem);
	Vector_Set(_heap->m_vec,0,lastElem);
	_heap->m_size--;
	HeapifyRec(_heap,0);

	return max;
}



/*get number of elements in the vector*/
size_t Heap_Size(const Heap* _heap)
{
	if (!_heap)
	{
		return 0;
	}

	return _heap->m_size;
}



Heap* Heap_Sort(Vector* _vec, LessThanComparator _pfLess)
{
	Heap* heap;
	void* elem1;
	void* elem2;
	size_t originalHeapSize,i;

	if (!_vec || !_pfLess)
	{
		return NULL;
	}

	heap=Heap_Build(_vec,_pfLess);
	originalHeapSize=Heap_Size(heap);
	i=originalHeapSize-1;

	for(; i>0; i--)
	{
		/*swap first and last elments*/
		Vector_Get(heap->m_vec, 0, &elem1); 	
		Vector_Get(heap->m_vec, i, &elem2);
		Vector_Set(heap->m_vec, i, elem1);
		Vector_Set(heap->m_vec, 0, elem2);

		heap->m_size--;
		HeapifyRec(heap,0);
		
	}

	heap->m_size=originalHeapSize;
	return heap;
}







