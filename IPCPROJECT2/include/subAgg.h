#ifndef __SUBAGR_H__
#define __SUBAGR_H__

#include "cdr.h"
#include "ConcurentHash.h"
#include "Subscriber.h"
/** 
 *  @file subAgr.h
 *  @brief create an agregator for subscribers.
 *	
 *  @details  the agregator is based on concurent hashMap.
 *	multi threads framework
 *
*  @author benebrhi samuel  (benebrhi@gmail.com)
 * 
 *  @bug No known bugs!
 */
typedef ConcurentHash SubAgr;

typedef enum SubAgr_Result
{
	SUBAGR_SUCCESS,
	SUBAGR_ALLOCATION_ERROR,
	SUBAGR_ERROR
}SubAgr_Result;

typedef size_t (*HashFunction)(const void* _key);
typedef int (*EqualityFunction)(const void* _firstKey, const void* _secondKey);

/** 
 * @brief Create a new SubAgr map with given capcity and key characteristics.
 **@param[in] _capacity - Expected max capacity 
 * 						  actuall capacity will be equal to nearest larger prime number.
 * @param[in] _numberOfLocker - number of lockers .
 * @return newly created SubAgr or null on failure
 */
SubAgr* SubAgr_Create(size_t capacity, size_t _numberOfLocker);

/**
 * @brief destroy SubAgr and set *_subAgr to null
 * @param[in] _subAgr :subAgr to be destroyed
 * @param[optional] _keyDestroy : pointer to function to destroy keys
 * @param[optional] _valDestroy : pointer to function to destroy values 
 * @details optionally destroy all keys and values using user provided functions
 */
void SubAgr_Destroy(SubAgr** _subAgr,void (*_keyDestroy)(void* _key), void (*_valDestroy)(void* _value));


/** 
 * @brief update a value find by key
 * complexty(1)
 * @param[in] _subAgr - _subAgr to use, must be initialized
 * @param[in] __cdr - key to serve as index for search
 * @param[in] _f - pointer to function to update the data.

 * @return Success indicator
 * @retval  MAP_SUCCESS	on success
 * @retval  MAP_KEY_NULL_ERROR
 * @retval  MAP_KEY_NOT_FOUND_ERROR if key not found
 * @retval  MAP_UNINITIALIZED_ERROR
 * 
 * @warning key must be unique and destinct
 */
SubAgr_Result SubAgr_update(SubAgr* _subAgr,CDR* _cdr);
SubAgr_Result SubAgr_getQuery(SubAgr* _subAgr, void* _key,Subscriber* _subcriber);
#endif
