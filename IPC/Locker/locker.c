#include "locker.h"

#include <pthread.h> /* pthread_mutex_t */
#include <stdlib.h>	 /* malloc			*/


struct Locker
{
	pthread_mutex_t* 	m_lockers;
	size_t				m_numberOfLockers;
};
/*#######################STATIC###############################*/
Locker_Result 	Locker_init(Locker* _locker, size_t _numberOfLockers);
/*###########################################################*/
Locker* Locker_Create(size_t _numberOfLockers)
{
	Locker* 		newLocker 	= NULL;
	Locker_Result  	result 		= LOCKER_SUCCESS;
	newLocker = (Locker*)malloc(sizeof(Locker));
	if(NULL == newLocker)
	{
		return NULL;
	}

	result = Locker_init(newLocker, _numberOfLockers);
	if(result != LOCKER_SUCCESS)
	{
		free(newLocker);
		return NULL;
	}
	return newLocker;
}

void Locker_Destroy(Locker** _locker)
{
	int i 				= 0;
	size_t nOfLockers 	= 0;
	if(NULL == _locker)
	{
		return ;
	}
	nOfLockers = (*_locker) -> m_numberOfLockers;
	for(;i < nOfLockers; ++i)
	{
		pthread_mutex_destroy(&((*_locker) -> m_lockers[i]));
	}
	free((*_locker) -> m_lockers);
	free(*_locker);
	*_locker = NULL;
}

Locker_Result Locker_Lock(Locker* _locker, size_t _index)
{
	if(NULL == _locker)
	{
		return LOCKER_UNITIALIZED_ERROR;
	}

	if (pthread_mutex_lock(&(_locker ->m_lockers[_index])) != 0)
	{
		return LOCKER_FAIL_ERROR;
	}
	return LOCKER_SUCCESS;
}

Locker_Result Locker_Unlock(Locker* _locker, size_t _index)
{
	if(NULL == _locker)
	{
		return LOCKER_UNITIALIZED_ERROR;
	}

	if (pthread_mutex_unlock(&(_locker ->m_lockers[_index])) != 0)
	{
		return LOCKER_FAIL_ERROR;
	}

	return LOCKER_SUCCESS;
}
/*********************************STATIC*************************************/

Locker_Result 	Locker_init(Locker* _locker, size_t _numberOfLockers)
{
	int i = 0;
	_locker -> m_lockers = (pthread_mutex_t*)malloc(sizeof(pthread_mutex_t) * _numberOfLockers);
	if(NULL ==_locker -> m_lockers)
	{
		return LOCKER_ALLOCATION_ERROR;
	}
	for(; i < _numberOfLockers;i++)
	{
		if(pthread_mutex_init(&(_locker ->m_lockers[i]),NULL) != 0)
		{
			return LOCKER_FAIL_ERROR;
		}
	}
	_locker -> m_numberOfLockers = _numberOfLockers;
	return LOCKER_SUCCESS;
}
