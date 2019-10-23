#include <stdlib.h>
#include"HashMap.h"
#include"list.h"
#include"list_itr.h"
#include"list_functions.h"

#define CHECKCAPACITY			if(_capacity == 0) return NULL;
#define CHECKNULLPOINTER(X)		if(NULL == (X)) return NULL;
#define CHECKINPUT(X)			if(NULL == (X)) return MAP_KEY_NULL_ERROR;
#define	CHECKPOINTER(X)			if(NULL == (X)) return MAP_UNINITIALIZED_ERROR;
#define CHECKKEY(X)				if(NULL == (X)) return MAP_KEY_NULL_ERROR;
#define COMPARATOR(X)			(X) -> m_KeysComparator
#define BUCKETS(X)				(X) -> m_buckets
#define HASH(X)					(X) -> m_hashFunc
#define CAPACITY   				_HashMap -> m_capacity

#define FALSE					0
#define TRUE					1

typedef struct Map
{
	void* m_value;
	void* m_key;

}Map;

struct HashMap
{
	HashFunction 			m_hashFunc;
	EqualityFunction 		m_KeysComparator;
	List*					*m_buckets;
	size_t 					m_capacity;
	size_t 					m_numOfItems;
};

/*################################STAITCS DECLARATIONS######################*/
static HashMap*				alllocationHash(void);
static int 					FindNextPrimeNumber(int _number);
static List**				allocationBuckets(int _size);
static void					initHash(HashMap* _hash,int _size, HashFunction _hashFunc, EqualityFunction _keysEqualFunc);
static int 					isPrime(size_t _num);
static int 					IsListExist(HashMap* _HashMap, int index);
static Map_Result			CreateList(HashMap* _HashMap, int index);
static void*				MatchTwoKeys(HashMap* _HashMap, int index, void* _key);
static Map*					CreateMap(void* _key,void* _value);
static void					InsertItem(HashMap* _HashMap,int index,Map* _map);
static int                  comparatorNode(HashMap* _HashMap,void* _a, void* _b);
static int 					IsEmpty(HashMap* _hashMap, int index);
static void 				ExtractMap(ListItr removeMap,void** _pKey,void** _pValue);
static void 				DestroyBuckets(HashMap* _HashMap, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
static void 				DestroyMap(Map* map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));
static int					List_IsEmpty(List* _list);
/*#########################################################################*/
HashMap* HashMap_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	int actualCapacity;
	HashMap* newHash;

	CHECKCAPACITY
	CHECKNULLPOINTER(_hashFunc);
	CHECKNULLPOINTER(_keysEqualFunc)

	newHash = alllocationHash();
	CHECKNULLPOINTER(newHash);

	actualCapacity = FindNextPrimeNumber(_capacity);
	BUCKETS(newHash) = allocationBuckets(actualCapacity);
	if(BUCKETS(newHash) == NULL)
	{
		free(newHash);
		return NULL;
	}

	initHash(newHash, actualCapacity, _hashFunc, _keysEqualFunc);

	return newHash;

}

void HashMap_Destroy(HashMap** _hashMap, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	
	if (!_hashMap || *_hashMap)
	{	
		return;
	}

	DestroyBuckets(*_hashMap, _keyDestroy, _valDestroy);
	
	free(*_hashMap);
	*_hashMap = NULL;
}

Map_Result HashMap_Insert(HashMap* _HashMap, const void* _key, const void* _value)
{
	int index;
	Map* newMap;
	CHECKPOINTER(_HashMap);
	CHECKKEY(_key);
	CHECKINPUT(_value);

	index = HASH(_HashMap)(_key);
	index = index % _HashMap -> m_capacity;

	if(!IsListExist(_HashMap, index))
	{
		if(CreateList(_HashMap,index) != MAP_SUCCESS)
		{
			return MAP_ALLOCATION_ERROR;
		}
	}
	if(!MatchTwoKeys(_HashMap,index,(void*) _key))
	{
		newMap = CreateMap((void*)_key,(void*) _value);
		if(!newMap)
		{
			return MAP_ALLOCATION_ERROR;
		}
		InsertItem(_HashMap,index,newMap);
		return MAP_SUCCESS;
	}
	return MAP_KEY_DUPLICATE_ERROR;
}


Map_Result HashMap_Remove(HashMap* _HashMap, const void* _searchKey, void** _pKey, void** _pValue)
{
	int index;
	ListItr itr;
	Map* removeMap;

	CHECKPOINTER(_HashMap);
	CHECKKEY(_searchKey);
	CHECKINPUT(_pKey);
	CHECKINPUT(_pValue);

	index = HASH(_HashMap)(_searchKey) % CAPACITY;

	if(!IsListExist(_HashMap, index) || IsEmpty(_HashMap, index))
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}

	itr = MatchTwoKeys(_HashMap,index,(void*) _searchKey);
	if(!itr)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}

	removeMap = ListItr_Remove(itr);
	_HashMap -> m_numOfItems --;
	ExtractMap(removeMap, _pKey, _pValue);
	free(removeMap);

	return MAP_SUCCESS;

}
Map_Result HashMap_Find(const HashMap* _HashMap, const void* _searchKey, void** _pValue)
{
	int index;
	ListItr itr;
	void* key;
	Map* findMap;

	CHECKPOINTER(_HashMap);
	CHECKKEY(_searchKey);
	
	index = HASH(_HashMap)(_searchKey) % CAPACITY;

	if(!IsListExist((HashMap*)_HashMap, index) || IsEmpty((HashMap*)_HashMap, index))
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}

	itr = MatchTwoKeys((HashMap*)_HashMap,index,(void*) _searchKey);
	if(!itr)
	{
		return MAP_KEY_NOT_FOUND_ERROR;
	}
	findMap = ListItr_Get(itr);
	if(_pValue != NULL)
	{
		ExtractMap(findMap,&key,_pValue);
	}

	return MAP_SUCCESS;

}

size_t HashMap_Size(const HashMap* _HashMap)
{
	CHECKPOINTER(_HashMap);

	return _HashMap ->m_capacity;
}
size_t HashMap_ForEach(const HashMap* _HashMap, KeyValueActionFunction _action, void* _context)
{
	int capacity, i;
	ListItr itr, begin, end;
	void* elem;
	size_t count = 0;
	CHECKPOINTER(_HashMap);
	CHECKPOINTER(_action);

	capacity = CAPACITY;
	for(i = 0; i < capacity;++i)
	{
		if(IsListExist((HashMap*) _HashMap, i))
		{

			begin = ListItr_Begin(BUCKETS(_HashMap)[i]);
			end   = ListItr_End(BUCKETS(_HashMap)[i]);

			for (itr = begin ; !ListItr_Equals(itr, end); itr = ListItr_Next(itr))
			{
				elem = ListItr_Get(itr);
				if (elem)
				{
					if (_action(((Map*)elem)->m_key,((Map*)elem)->m_value, _context) == 0)
					{
					return count;
					}
					count++;
				}
			}
		}

	
	}
	return count;
}
/*#############################################STATIC##########################################*/
/**********************CREATE STATIC********************************/
static HashMap*	alllocationHash(void)
{
	return (HashMap*)malloc(sizeof(HashMap));
}

static List** allocationBuckets(int _size)
{
	return (List**)calloc(_size, sizeof(List*));
}

static void	initHash(HashMap* _hash,int _size, HashFunction _hashFunc, EqualityFunction _keysEqualFunc)
{
	_hash -> m_numOfItems = 0;
	_hash -> m_capacity = _size;
	_hash -> m_hashFunc = _hashFunc;
	_hash -> m_KeysComparator = _keysEqualFunc;
}

static int FindNextPrimeNumber(int _number)
{
	while(isPrime(_number) != TRUE)
	{
		_number++;
	}
	return _number;
}

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


/*********************INSERT STATIC********************/
static int IsListExist(HashMap* _HashMap, int index)
{
	return BUCKETS(_HashMap)[index] != NULL;
}

static Map_Result CreateList(HashMap* _HashMap, int index)
{
	BUCKETS(_HashMap)[index] = List_Create();
	if(BUCKETS(_HashMap)[index] == NULL)
	{
		return MAP_ALLOCATION_ERROR;
	}
	return MAP_SUCCESS;
}

static void* MatchTwoKeys(HashMap* _HashMap, int _index,void* _key)
{
	ListItr itr, begin, end;
	void* elem;
	begin = ListItr_Begin(BUCKETS(_HashMap)[_index]);
	end   = ListItr_End(BUCKETS(_HashMap)[_index]);

	for (itr = begin ; !ListItr_Equals(itr, end); itr = ListItr_Next(itr))
	{
		elem = ListItr_Get(itr);
		if (elem)
		{
			if (comparatorNode(_HashMap,(void*)( ((Map*)elem)->m_key), _key))
			{
				return itr;
			}
		}
	}

	return NULL;
}

static Map*	CreateMap(void* _key,void* _value)
{
	Map* newMap = (Map*) malloc(sizeof(Map));
	CHECKNULLPOINTER(newMap);
	newMap -> m_key = _key;
	newMap -> m_value = _value;
	
	return newMap;
}

static void	InsertItem(HashMap* _HashMap,int index,Map* _map)
{
	ListItr_InsertBefore(ListItr_End(BUCKETS(_HashMap)[index]),_map);
	_HashMap -> m_numOfItems++;
}

static int comparatorNode(HashMap* _HashMap,void* _a, void* _b)
{
	return COMPARATOR(_HashMap)(_a, _b);
}
/*********************REMOVE STATIC*****************************/
static int IsEmpty(HashMap* _HashMap, int _index)
{
	return ListItr_Equals( ListItr_Begin(BUCKETS(_HashMap)[_index]),ListItr_End(BUCKETS(_HashMap)[_index]));
}

static void ExtractMap(ListItr _removeMap,void** _pKey,void** _pValue)
{
	*_pKey = ((Map*)_removeMap) -> m_key;
	*_pValue = ((Map*)_removeMap) -> m_value;
	
}
/******************************************************/

/*************************DESTROY STATIC*********************************/
static void DestroyBuckets(HashMap* _HashMap, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	int i;
	Map* map = NULL;

	for (i = 0; i < CAPACITY; ++i)
	{
		if(NULL == _HashMap->m_buckets[i])
		{
			continue;
		}

		while(! List_IsEmpty(_HashMap->m_buckets[i]) )
		{
			List_PopTail(_HashMap->m_buckets[i] , (void**)&map);
			DestroyMap(map, _keyDestroy, _valDestroy);
		}

		List_Destroy(&(_HashMap->m_buckets[i]), NULL);
	}
	free(_HashMap->m_buckets);
	
}

static void DestroyMap(Map* map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value) )
{
	if (map)
	{
		if (_keyDestroy)
		{
			_keyDestroy(map->m_key);
		}

		if (_valDestroy)
		{
			_valDestroy(map->m_value);
		}

		free(map);
	}
}


/*TODO*/
static int List_IsEmpty(List* _list)
{
	return 0;
}

