#ifndef MUTEX_H
#define MUTEX_H

#include<pthread.h>

#include "NonCopyable.h"

#include "MutexException.h"
namespace advcpp
{
#define NOEXCEPT throw()
class CondVariable;


class Mutex:NonCopyable
{
    //template <typename T> 
    friend  class CondVariable;//::CondWait(Mutex& mutex,T);
public:
    Mutex() throw(MutexException);
    ~Mutex() NOEXCEPT;

    void Lock() throw(MutexException);
    void Unlock() throw(MutexException);

    const bool& IsLock() const;

private:
    pthread_mutex_t m_id;
    bool m_IsLock;
};


}



#endif