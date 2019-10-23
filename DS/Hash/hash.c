/*
	for status: - 0 empty
				- 1 not empty
				- 2 delete
*/

#include<stdio.h>
#include<stdlib.h>
#include"ADTErr.h"
#include"hash.h"

#define MAGIC_NUMBER 0XBEEFBEEF
#define CHECK_POINTER(X) 			if(!(X)) return ERR_UNINITIALIZED; 

#define CAPACITY(X)				((X) -> m_capacity)
#define NITEMS(X)				((X) -> m_numOfItems)
#define COUNTER_INSERTIONS(X)	((X) -> m_counterOfInsertions)
#define COUNTER_REHASHOPS(X)	((X) -> m_allRehashOperations)
#define MAX_REHASH_OPS(X)		((X) -> m_maxOfRehashOperations)
#define ITEMS(X)				((X) -> m_data)
#define STATUS_ARR(X)			((X) -> m_status)
#define MAGIC(X)				((X) -> m_magicNumber)
#define FACTOR					1.3

struct Hash
{
	size_t m_magicNumber;
	int* m_data;
	int* m_status;
	size_t m_capacity;
	size_t m_numOfItems;
	size_t m_maxOfRehashOperations;
	size_t m_counterOfInsertions;
	size_t m_allRehashOperations;

};
/*#################STATIC FUNCTIONS DECLARATION############################*/
static void initialiseStruct(Hash* _hash, size_t _size);
static size_t firstNextPrime(size_t _num);
static int isPrime(size_t _num);
static size_t HashFunction(const Hash* _hash, size_t _data, int _rehashNum);
static void InsertElement(Hash* _hash, int _data,int _index , int _rehashNum);
static void removeElement(Hash* _hash,int _data,int _index);
/*##########################################################################*/


Hash* HashCreate(const size_t _size)
{
	Hash* newHash;
	

	if(0 == _size)
	{
		return NULL;
	}

	newHash = (Hash*) calloc(1,sizeof(Hash));
	if(!newHash)
	{
		return NULL;
	}


	initialiseStruct(newHash, _size);
	if (MAGIC(newHash) == MAGIC_NUMBER)
	{
		return newHash;
	}
	else 
	{
		return NULL;
	}

}

void HashDestroy(Hash* _hash)
{
	if(NULL ==_hash || MAGIC(_hash) != MAGIC_NUMBER)
	{
		return;
	}
	free(STATUS_ARR(_hash));

	free(ITEMS(_hash));
	
	free(_hash);
}


ADTErr HashInsert(Hash* _hash , int _data)
{
	int index;
	int i = 0;
	CHECK_POINTER(_hash);

	index = HashFunction(_hash, _data, i);

	/*if we have colision*/
	while(STATUS_ARR(_hash)[index] == 1)
	{
		/*avoid infinite loop*/
		if(i < CAPACITY(_hash))
		{
			index = HashFunction(_hash,_data, ++i);
		}
		else 
		{
			return ERR_OVERFLOW;
		}
	}

	InsertElement(_hash,_data, index, i);

	return ERR_OK;

}



ADTErr HashRemove(Hash* _hash, int _data)
{
	int i = 0, index = 0;
	CHECK_POINTER(_hash);

	if(NITEMS(_hash) == 0)
	{
		return ERR_EMPTY;
	}

	index = HashFunction(_hash, _data , i);

	/*if we reach an empty place or we have done more rehash than the max rehash of insertion*/
	while(STATUS_ARR(_hash)[index] != 0 && MAX_REHASH_OPS(_hash) <= i)
	{
		if (ITEMS(_hash)[index] != _data)
		{
			index = HashFunction(_hash, _data , ++i);
		}
	}
	if (ITEMS(_hash)[index] != _data)
	{
		return ERR_NOT_FOUND;
	}

	removeElement(_hash,_data,index);

	return ERR_OK;

}

int HashIsFound(const Hash* _hash, int _data)
{
	int i = 0, index = 0;
	CHECK_POINTER(_hash);

	if(NITEMS(_hash) == 0)
	{
		return ERR_EMPTY;
	}

	index = HashFunction(_hash, _data , i);

	/*if we reach an empty place or we have done more rehash than the max rehash of insertion*/
	while(STATUS_ARR(_hash)[index] != 0 && MAX_REHASH_OPS(_hash) <= i)
	{
		if (ITEMS(_hash)[index] != _data)
		{
			index = HashFunction(_hash, _data , ++i);
		}

		if(STATUS_ARR(_hash)[index] == 1 && ITEMS(_hash)[index] == _data)
		{
			return TRUE;
		}
	}
	return FALSE;
}

size_t HashCapacity(const Hash* _hash)
{
	CHECK_POINTER(_hash);

	return CAPACITY(_hash);
}

size_t HashNumOfItems(const Hash* _hash)
{
	CHECK_POINTER(_hash);

	return NITEMS(_hash);
}

double HashAverageRehashes(const Hash* _hash)
{
	CHECK_POINTER(_hash);

	return COUNTER_REHASHOPS(_hash ) / COUNTER_INSERTIONS(_hash) ;
}

size_t HashMaxReHash(const Hash* _hash)
{
	CHECK_POINTER(_hash);

	return MAX_REHASH_OPS(_hash);
}


void HashPrint(const Hash* _hash)
{
	int i;
	if(NULL == _hash)
	{
		return;
	}

	for ( i = 0; i <= CAPACITY(_hash); ++i)
	{
		if(STATUS_ARR(_hash)[i] == 1)
		{
			printf("at index %d : %d\n",i, ITEMS(_hash)[i]);
		}
	}

}


/*###############STATIC FUNCTIONS #######################*/
static int isPrime(size_t _num)
{
	int i;
	for(i = 2; i* i <= _num;i++)
	{
		if(_num %i == 0)
			return FALSE;
	}
	return TRUE;
}




static size_t firstNextPrime(size_t _num)
{
	while(isPrime(_num) != TRUE)
	{
		_num++;
	}
	return _num;
}


static void initialiseStruct(Hash* _hash, size_t _size)
{
	int effCapacity;

	ITEMS(_hash) = (int*)malloc(_size * sizeof(int));
	if(!ITEMS(_hash))
	{
		free(_hash);
		return ;
	}

	STATUS_ARR(_hash) = (int*)calloc(_size, sizeof(int));
	if(!STATUS_ARR(_hash))
	{
		free(_hash);
		return ;
	}

	MAGIC(_hash) = MAGIC_NUMBER;

	CAPACITY(_hash) = firstNextPrime(_size * FACTOR);
}

static size_t HashFunction(const Hash* _hash, size_t _data, int _rehashNum)
{

	return ((2 * _data % CAPACITY(_hash)) + _rehashNum) % CAPACITY(_hash);
}



static void InsertElement(Hash* _hash, int _data, int _index , int _rehashNum)
{

	STATUS_ARR(_hash)[_index] = 1;
	ITEMS(_hash)[_index] = _data;
	NITEMS(_hash) += 1;
	COUNTER_INSERTIONS(_hash) += 1;
	COUNTER_REHASHOPS(_hash) += _rehashNum;

	if(_rehashNum > MAX_REHASH_OPS(_hash))
	{
		MAX_REHASH_OPS(_hash) = _rehashNum;
	}
}

static void removeElement(Hash* _hash,int _data,int _index)
{
	NITEMS(_hash) -= 1;
	STATUS_ARR(_hash)[_index] = 2;
}