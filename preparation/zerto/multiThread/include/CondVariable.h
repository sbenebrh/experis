#ifndef CONDVARIABLE_H
#define CONDVARIABLE_H


#include <pthread.h>
#include <stdexcept>
#include <cassert>
#include "NonCopyable.h"
#include "Mutex.h"


namespace advcpp
{

class CondVariableException:public std::exception
{
public:
    CondVariableException(int errnum);
};


#define NOEXCEPT throw()
class Mutex;
class CondVariable:NonCopyable
{
public:
    CondVariable() throw (CondVariableException);
    ~CondVariable() NOEXCEPT;

    template<typename Predicate>
    void CondWait(Mutex& mutex, Predicate  pred) throw(CondVariableException);

    void CondSignal() throw (CondVariableException);
    void CondBroadcast() throw (CondVariableException);

private:
    pthread_cond_t m_id;
};

template<typename Predicate>
void CondVariable::CondWait(Mutex& mutex,Predicate  pred) throw (CondVariableException)
{
    /*Mutex m;
    m.Lock();
    if(!mutex.IsLock())
    {
        assert(false and "impossible to wait until the mutex is not locked");
    }
    m.Unlock();*/
    while(!pred())
    {
        int result = 0;
        if( (result = pthread_cond_wait(&m_id, &mutex.m_id))!= 0)
        {
            throw CondVariableException(result);
        }
    }
}

}


#endif