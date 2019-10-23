/** 
 * @brief Create a Generic Vector data type
 * that stores pointer to user provided elements of generic type
 * The Vector is heap allocated and can grow and shrink on demand.
 * 
 * @author Samuel ben ibgui 
 */ 

#include<stddef.h> /*size_t*/
#include<stdlib.h> /*malloc */
#include"vector.h"

#define CHECKINPUTNULL(X,Y)		if(!(X) && !(Y)) return NULL;
#define CHECKPOINTERNULL(X)		if(NULL == (X)) return NULL;
#define CHEKPOINTER(X)			if(NULL == (X)) return VECTOR_UNITIALIZED_ERROR;

#define ITEMS(X)				(X) -> m_items
#define SIZE(X)					(X) -> m_size
#define NITEMS(X)				(X) -> m_nitems
#define BLOCKSIZE(X)			(X) -> m_blockSize
#define ORIGINALSIZE(X)			(X) -> m_originalSize

#define FACTOR					1.3
#define FACTOR_FREE				2

struct Vector
{
	int 	m_originalSize;
	void* 	*m_items;
	size_t 	m_size;
	size_t 	m_nitems;
	size_t 	m_blockSize;
};

/*##############STATIC DECLARATIONS#############*/
static void 			initializeVector(Vector* _newVector,size_t _initialCapacity, size_t _blockSize);
static Vector_Result 	reSize(Vector* _vector,size_t _resize);
static void 			inserItem(Vector* _vector, void* _item);
static int 				IsAllowedRealloc(const Vector* _vector);
static int 				IsFull(const Vector* _vector);
static void 			destroyInsideElement(Vector* _vector,void(*_elementDestroy)(void* _item));
static int 				moreThanTwoFreeBlock(const Vector* _vector);
static int 				IsUnderOriginalSize(const Vector* _vector);
static int 				checkFreeSpace(const Vector* _vector);
static int 				IsEmpty(const Vector* _vector);
static int 				IsOutOfBound(const Vector* _vector, size_t _index);
/*###############################################*/

Vector* Vector_Create(size_t _initialCapacity, size_t _blockSize)
{
	Vector* newVector = NULL;

	CHECKINPUTNULL(_initialCapacity, _blockSize);

	newVector = (Vector*) malloc(sizeof(Vector));
	CHECKPOINTERNULL(newVector);

	initializeVector(newVector, _initialCapacity, _blockSize);

	if(NULL == ITEMS(newVector) )
	{
		free(newVector);
		return NULL;
	}

	return newVector;

}



void Vector_Destroy(Vector** _vector, void (*_elementDestroy)(void* _item))
{
	int i;

	if(_vector)
	{
		if(*_vector)
		{
			destroyInsideElement(*_vector,(*_elementDestroy));

			free(ITEMS(*_vector));
			free(*_vector);
			*_vector = NULL;
		}
	}
}



Vector_Result Vector_Append(Vector* _vector, void* _item)
{
	CHEKPOINTER(_vector);
	CHEKPOINTER(_item);

	/*if the vector if full and it can t be resized*/
	if(IsFull(_vector))
	{
		if(! IsAllowedRealloc(_vector))
		{
			return VECTOR_ALLOCATION_ERROR;
		}
		/*neeed reallocation*/
		if(IsAllowedRealloc(_vector))
		{
			if(reSize(_vector, FACTOR) == VECTOR_ALLOCATION_ERROR)
			{
				return VECTOR_ALLOCATION_ERROR;
			}
		}
	}

	inserItem(_vector, _item);

	return VECTOR_SUCCESS;
}


Vector_Result Vector_Remove(Vector* _vector, void** _pValue)
{
	CHEKPOINTER(_vector);
	CHEKPOINTER(_pValue);

	if(IsEmpty(_vector))
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}

	/*get the element to destroy*/
	*_pValue = ITEMS(_vector)[NITEMS(_vector) - 1];
	NITEMS(_vector) -=1;

	/*if we have more to 2 blocksize free resize to 1*/
	if(moreThanTwoFreeBlock(_vector))
	{
		if(reSize(_vector, -1) == VECTOR_ALLOCATION_ERROR)
		{
			return VECTOR_ALLOCATION_ERROR;
		}
	}
	return VECTOR_SUCCESS;
}

Vector_Result Vector_Get(const Vector* _vector, size_t _index, void** _pValue)
{
	CHEKPOINTER(_vector);
	CHEKPOINTER(_pValue);

	if(IsOutOfBound(_vector, _index) == 1)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}

	*_pValue = ITEMS(_vector)[_index];

	return VECTOR_SUCCESS;
}


Vector_Result Vector_Set(Vector* _vector, size_t _index, void*  _value)
{
	CHEKPOINTER(_vector);
	CHEKPOINTER(_value);

	if(IsOutOfBound(_vector, _index) == 1)
	{
		return VECTOR_INDEX_OUT_OF_BOUNDS_ERROR;
	}

	ITEMS(_vector)[_index] = _value;

	return VECTOR_SUCCESS;
}

size_t Vector_Size(const Vector* _vector)
{
	if(NULL == _vector)
	{
		return 0;
	}

	return NITEMS(_vector);
}

size_t Vector_Capacity(const Vector* _vector)
{
		CHEKPOINTER(_vector);

		return SIZE(_vector);
}

size_t Vector_ForEach(const Vector* _vector, VectorElementAction _action, void* _context)
{
	int i = 0;
	int size;

	CHEKPOINTER(_vector);
	CHEKPOINTER(_action);

	size = NITEMS(_vector);

	for(;i < size; ++i)
	{
		if(_action(ITEMS(_vector)[i], i, _context) == 0)
		{
			break;
		}
	}
	return i;


}








/*################STATIC FUNCTIONS#####################*/
static void initializeVector(Vector* _newVector,size_t _initialCapacity, size_t _blockSize)
{
	NITEMS(_newVector) = 0;
	SIZE(_newVector) = _initialCapacity;
	ORIGINALSIZE(_newVector) = _initialCapacity;
	BLOCKSIZE(_newVector) = _blockSize;
	ITEMS(_newVector) = (void**) malloc(SIZE(_newVector)* sizeof(void*));
}

static Vector_Result reSize(Vector* _vector,size_t _resize)
{
	void* *temp = (void**) realloc(ITEMS(_vector), (SIZE(_vector) +(BLOCKSIZE(_vector) * _resize)) * sizeof(void*));
	if(NULL == temp)
	{
		return VECTOR_ALLOCATION_ERROR;
	}

	ITEMS(_vector) = temp;
	SIZE(_vector) += BLOCKSIZE(_vector) * _resize;

	return VECTOR_SUCCESS; 
}

static void inserItem(Vector* _vector, void* _item)
{
	ITEMS(_vector)[NITEMS(_vector)] = _item;
	NITEMS(_vector) += 1;
}
static int IsAllowedRealloc(const Vector* _vector)
{
	return IsFull(_vector) && BLOCKSIZE(_vector) > 0;
}

static int IsFull(const Vector* _vector)
{
	return SIZE(_vector) == NITEMS(_vector);
}

static void destroyInsideElement(Vector* _vector,void(*_elementDestroy)(void* _item))
{
	int i;
	size_t nelements = NITEMS(_vector);

	if((*_elementDestroy) == NULL)
	{
		return;
	}

	for(i = 0; i < nelements; ++i)
	{
		(*_elementDestroy)(ITEMS(_vector)[i]);
	}
}

static int moreThanTwoFreeBlock(const Vector* _vector)
{
	return checkFreeSpace(_vector) && IsUnderOriginalSize(_vector);
}

static int IsUnderOriginalSize(const Vector* _vector)
{
	return (SIZE(_vector) - BLOCKSIZE(_vector) )> ORIGINALSIZE(_vector);
}

static int checkFreeSpace(const Vector* _vector)
{
	return (SIZE(_vector) - NITEMS(_vector) )>= (FACTOR_FREE * BLOCKSIZE(_vector));
}


static int IsEmpty(const Vector* _vector)
{
	return NITEMS(_vector) == 0;
}

static int IsOutOfBound(const Vector* _vector, size_t _index)
{
	return _index >= NITEMS(_vector)  ;
}
