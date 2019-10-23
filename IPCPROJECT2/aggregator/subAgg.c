#include "subAgg.h"

#include <string.h> /*memcpy*/
#include <stdlib.h>

#include "ConcurentHash.h"
#include "cdr.h"
#include "Subscriber.h"
#include "zlog4c.h"

#define TRUE 1
#define FALSE 0

/*#################################################################################*/
static void* 	SubAgr_edit(void* _value, void* _context);
static int 		equalFunc(const void* _firstKey, const void* _secondKey);
static size_t 	hashFunc(const void* _key);
static void* 	copyFunc (void* _cdr1, void* _cdr2);
/*#################################################################################*/

SubAgr* SubAgr_Create(size_t capacity, size_t _numberOfLocker)
{
	ZLOG(LOG_TRACE, "SubAgr_Create");
	SubAgr* newSubAgr  = (SubAgr*) ConcurentHash_Create( capacity,  hashFunc, equalFunc, _numberOfLocker);
	return newSubAgr;

}

void SubAgr_Destroy(SubAgr** _subAgr,void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value))
{
	if(_subAgr == NULL || *_subAgr == NULL)
	{
		return;
	}
	ZLOG(LOG_TRACE, "SubAgr_Destroy");
	ConcurentHash_Destroy(_subAgr, _keyDestroy, _valDestroy);	
}

SubAgr_Result SubAgr_update(SubAgr* _subAgr,CDR* _cdr)
{
	size_t* key 				= NULL;

	if(NULL == _subAgr)
	{
		return SUBAGR_ALLOCATION_ERROR;
	}
	ZLOG(LOG_TRACE, "SubAgr_update");
	
	key = malloc(sizeof(size_t));
	*key = _cdr -> m_IMSI;
	

	ConcurentHash_update(_subAgr, key, SubAgr_edit, _cdr); 
	
	return SUBAGR_SUCCESS;
}

SubAgr_Result SubAgr_getQuery(SubAgr* _subAgr, void* _key,Subscriber* _sub)
{
	if(ConcurentHash_Get(_subAgr, _key, copyFunc,_sub) == 0)
	{
		
		return SUBAGR_SUCCESS;
	}
	
	return SUBAGR_ERROR;
}
/**********************************************************/
void* SubAgr_edit(void* _value, void* _context)
{
	Subscriber* subscriber = NULL;
	if(NULL == _value)
	{
		subscriber = Subscriber_Create((CDR*)_context);
		return subscriber;
	}
	
	Subscriber_SetData((Subscriber*)_value,(CDR*) _context);
	return _value;
}

size_t hashFunc(const void* _key)
{
	return  *((int*)_key); 
}

int equalFunc(const void* _firstKey, const void* _secondKey)
{
	if (*(int*)_firstKey == *(int*)_secondKey)
	{
		return TRUE;
	}
	return FALSE;
}

void* copyFunc (void* _sub1, void* _sub2)
{
	int size = Subscriber_Size();
	memcpy(_sub2, _sub1, size);
	return _sub2;
}
