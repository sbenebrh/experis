#include "Mutex.h"

#include <cassert>

#include "CreationFailureException.h"

namespace advcpp
{

Mutex::Mutex() throw(MutexException)
:m_IsLock(false)
{
    int result = 0;
    if((result = pthread_mutex_init(&m_id,0)) != 0)
    {
        throw MutexException(result);
    }
}

Mutex::~Mutex() NOEXCEPT
{ 
    if(pthread_mutex_destroy(&m_id))
    {
        assert(false and "error destroy mutex");
    }
}

void Mutex::Lock() throw(MutexException)
{
    int result = 0;
    
    if((result = pthread_mutex_lock(&m_id) )!= 0)
    {
        throw MutexException(result);
    }
    m_IsLock = true;
    
}

void Mutex::Unlock() throw(MutexException)
{
    int result = 0;
    
    if((result = pthread_mutex_unlock(&m_id)) != 0)
    {
        throw MutexException(result);
    }
    m_IsLock = false;
   
}

const bool& Mutex::IsLock() const
{
    return m_IsLock;
}

}