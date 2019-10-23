#ifndef __AGGRMAN_H__
#define __AGGRMAN_H__
/** 
 * @brief Create an aggregator manager get number of thread ,capacity 
 * and store data.
 * 
 * @author: samuel ben ibgui(benebrhi@gmail.com)
 */ 
#include <stddef.h> /*size_t*/

#include "subAgg.h"
typedef enum Aggr_Result
{
	AGGR_SUCCESS,
	AGGR_NOT_INITILIZED_ERROR
}Aggr_Result;

typedef struct AggrMan AggrMan;

/**  
 * @brief Dynamically create a new Aggregator manager object of given capacity and  number of thread for the system
 * @param[in] _capacity -number of elements that can be stored in the aggregator (it should be improve by itself)
 * @param[in] _numberOfThreads -number of thread needed for this aggregator manager
 * @param[in] _subaggr -aggregator of subscriber
 * @param[in] _filename -use for attach to a channel
 * @param[in] _protocole -use for attach to a channel

 * @return AggMan* - on success / NULL on fail 
 *
 * @warning if _capacity is zero function will return NULL.
 */
AggrMan* AggrMan_Create(size_t _numberOfThreads, SubAgr* _subaggr,char* _filename, char _protocole);

/**
 * @brief destroy aggregator manager and set *_subAgr to null
 * @param[in] _pAgg : aggregator to be destroyed

 * @details optionally destroy all keys and values using user provided functions
 */
void AggrMan_Destroy(AggrMan** _pAgg);

#endif /*__AGGRMAN_H__*/
