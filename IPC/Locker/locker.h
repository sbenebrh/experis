#ifndef __LOCKER_H__
#define __LOCKER_H__
/**
*  @file locker.h
*  @brief create an array of locker framework base on mutex implementation
* should be compile with flag -pthread
*  @details
*  @author samuel ben Ibgui  (benebrhi@gmail.com)
* 
*  @bug No known bugs! 
 */
#include <unistd.h> /*size_t*/

typedef enum Locker_Result{
	LOCKER_SUCCESS = 0	,
	LOCKER_UNITIALIZED_ERROR	,
	LOCKER_ALLOCATION_ERROR,
	LOCKER_FAIL_ERROR 		
}Locker_Result;


typedef struct Locker Locker;
/** 
 * @brief Create a new locker struct 
 * @param[in] _numberOfLocker : number of locker is need

 * @return newly created Cdr or null on failure
 * @warning _attribut may be NULL and the locker will work according to pthread default configuration
 */
Locker* Locker_Create(size_t _numberOfLocker);

/**
 * @brief lock the locker
 * @param[in] _locker : pointer to the array of lockers 
 * @param[in] __lockerindex: the index of the locker to lock
 * @return Success indicator
 * @retval  LOCKER_SUCCESS	on success
 * @retval  LOCKER_UNITIALIZED
 * @retval  LOCKER_FAIL
 */
Locker_Result Locker_Lock(Locker* _locker, size_t _lockerindex);

/**
 * @brief Unlock the locker
 * @param[in] _locker : pointer to the array of lockers 
 * @param[in] __lockerindex: the index of the locker to unlock
 * @return Success indicator
 * @retval  LOCKER_SUCCESS	on success
 * @retval  LOCKER_UNITIALIZED
 * @retval  LOCKER_FAIL

 * @warning don't try to unlock a locker that is not locked 
 */
Locker_Result Locker_Unlock(Locker* _locker, size_t _lockerindex);

/**
 * @brief destroy Locker and set *_locker to null
 * @param[in] _locker : cdr to be destroyed
 */
void Locker_Destroy(Locker** _plocker);
#endif
