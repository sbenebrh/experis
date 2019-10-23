#include "ConcurentHash.h"

#include <stdlib.h> /* malloc 		*/

#include "zlog4c.h" /* zlog 		*/
#include "locker.h" /* Lock_create  */
#include "HashMap.h"

struct  ConcurentHash
{
	HashMap*  				m_hash; 				/* hasMap           */
	Locker*					m_arrlockers;			/* array of mutexs 	*/			
	HashFunction			m_hashFunc;
	size_t 					m_nOfLockers;
};
/*################STATIC##########################*/
static ConMap_Result 	CreateLockers(ConcurentHash* _concurentHash, size_t _numberOfLocker);
static void 		destroy_lockers(ConcurentHash* _concurentHash);
static size_t 		getLocker(const ConcurentHash* _concurentHash, const void* _key);
/*################################################*/
ConcurentHash* ConcurentHash_Create(size_t _capacity, HashFunction _hashFunc, EqualityFunction _keysEqualFunc,size_t _numberOfLocker)
{
	ConcurentHash* newConcurentHash = NULL;

	ZLOG(LOG_TRACE, "creation of concurentHash struct ...");

	newConcurentHash = (ConcurentHash*) malloc(sizeof(ConcurentHash));
	if(NULL == newConcurentHash)
	{
		ZLOG(LOG_DEBUG,"impossible to allocate for ConcurentHash");
		return NULL;
	}

	ZLOG(LOG_TRACE, "creation of HashMap ...");
	if((newConcurentHash -> m_hash = HashMap_Create(_capacity,_hashFunc,_keysEqualFunc)) == NULL)
	{
		ZLOG(LOG_DEBUG,"impossible to Create HashMap");
		free(newConcurentHash);
		return NULL;
	}
	
	ZLOG(LOG_TRACE, "creation of Mutexs array ...");
	if(CreateLockers(newConcurentHash, _numberOfLocker) != CONMAP_SUCCESS)
	{
		ZLOG(LOG_DEBUG,"impossible to Mutexs array");
		HashMap_Destroy(&(newConcurentHash -> m_hash), NULL, NULL);
		free(newConcurentHash);
		return NULL;
	}

	newConcurentHash -> m_hashFunc = _hashFunc;
	return newConcurentHash;
}

void ConcurentHash_Destroy(ConcurentHash** _map, void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	/*TODO fix problem to lock bucket or lock every locker*/
	ZLOG(LOG_TRACE, "start to destroy");
	HashMap_Destroy(&((*_map)->m_hash), _keyDestroy, _valDestroy);
	destroy_lockers(*_map);
	free(*_map);
	*_map = NULL;
}

ConMap_Result ConcurentHash_Insert(ConcurentHash* _map, const void* _key, const void* _value)
{
	ConMap_Result result 		= 0;
	size_t indexLocker	  	= 0;

	indexLocker = getLocker(_map, _key);

	ZLOG(LOG_TRACE, "start to lock");
	if(Locker_Lock(_map -> m_arrlockers, indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to lock");

	result = HashMap_Insert(_map -> m_hash, _key, _value);

	ZLOG(LOG_TRACE, "start to unlock");
	if(Locker_Unlock(_map -> m_arrlockers, indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to unlock");

	return result;
}

ConMap_Result ConcurentHash_Remove(ConcurentHash* _map, const void* _searchKey, void** _pKey, void** _pValue)
{
	ConMap_Result result 		= 0;
	size_t indexLocker	  	= 0;

	indexLocker = getLocker(_map, _searchKey);

	ZLOG(LOG_TRACE, "start to lock");
	if(Locker_Lock(_map -> m_arrlockers, indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to lock");

	result = HashMap_Remove(_map -> m_hash, _searchKey, _pKey, _pValue);

	ZLOG(LOG_TRACE, "start to unlock");
	if(Locker_Unlock(_map -> m_arrlockers,indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to unlock");

	return result;

}

ConMap_Result ConcurentHash_update(ConcurentHash* _map, const void* _searchKey, void*(*f)(void*, void*), void* _context)
{
	Map_Result result 		= 0;
	size_t indexLocker	  	= 0;
	void* pValue 			= NULL;
	void* newValue 			= NULL;
	if(NULL == _map)
	{
		return CONMAP_UNINITIALIZED_ERROR;
	}

	indexLocker = getLocker(_map, _searchKey);

	ZLOG(LOG_TRACE, "start to lock");
	if(Locker_Lock(_map -> m_arrlockers, indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to lock");

	result = HashMap_Find(_map -> m_hash,  _searchKey,  &pValue);
	newValue =  f(pValue,_context);
	if(result != MAP_SUCCESS)
	{
		
		HashMap_Insert( _map -> m_hash, _searchKey, newValue);
	}

	ZLOG(LOG_TRACE, "start to unlock");
	if(Locker_Unlock(_map -> m_arrlockers,indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to unlock");
	return CONMAP_SUCCESS;

}

ConMap_Result ConcurentHash_Find(const ConcurentHash* _map, const void* _searchKey, void** _pValue)
{
	ConMap_Result result 		= 0;
	size_t indexLocker	  		= 0;

	indexLocker = getLocker(_map, _searchKey);

	ZLOG(LOG_TRACE, "start to lock");
	if(Locker_Lock(_map -> m_arrlockers,indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to lock");

	result = HashMap_Find( _map -> m_hash,  _searchKey,  _pValue);

	ZLOG(LOG_TRACE, "start to unlock");
	if(Locker_Unlock(_map -> m_arrlockers,indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to unlock");

	return result;
}

ConMap_Result ConcurentHash_Get(const ConcurentHash* _map, const void* _searchKey, void*(*f)(void*,void*),void* getValue)
{
	ConMap_Result result 		= 0;
	size_t indexLocker	  		= 0;
	void* pValue 				= NULL;

	indexLocker = getLocker(_map, _searchKey);

	ZLOG(LOG_TRACE, "start to lock");
	if(Locker_Lock(_map -> m_arrlockers,indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to lock");

	result = HashMap_Find( _map -> m_hash,  _searchKey,  &(pValue));
	if(result != CONMAP_SUCCESS)
	{
		return CONMAP_KEY_NOT_FOUND_ERROR;
	}
	f(pValue, &getValue);

	ZLOG(LOG_TRACE, "start to unlock");
	if(Locker_Unlock(_map -> m_arrlockers,indexLocker) != LOCKER_SUCCESS)
	{
		return CONMAP_LOCKER_FAIL;
	}
	ZLOG(LOG_TRACE, "finish to unlock");

	return result;
}
/*TODO forEach but i get the same pb of destroy with the lockers*/
size_t CHashMap_ForEach(const ConcurentHash* _map, KeyValueActionFunction _action, void* _context)
{
	int res = 0;

	res=HashMap_ForEach(_map->m_hash,_action,_context);

	return res;
}
/*********************************************************/


static void destroy_lockers(ConcurentHash* _concurentHash)
{
	Locker_Destroy(&(_concurentHash -> m_arrlockers));
}

static size_t getLocker(const ConcurentHash* _concurentHash, const void* _key)
{
	size_t capacity = 0;
	int index 		= 0;

	capacity = HashMap_Size(_concurentHash -> m_hash);
	index = _concurentHash -> m_hashFunc(_key) % capacity;

	return index % _concurentHash -> m_nOfLockers;
}

static ConMap_Result 	CreateLockers(ConcurentHash* _concurentHash, size_t _numberOfLocker)
{
	_concurentHash -> m_arrlockers = Locker_Create(_numberOfLocker);
	if(_concurentHash -> m_arrlockers == NULL)
	{
		return CONMAP_ALLOCATION_ERROR;
	}
	_concurentHash -> m_nOfLockers = _numberOfLocker;
	return CONMAP_SUCCESS;
}
