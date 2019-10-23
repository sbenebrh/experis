#include "WaitableQueue.h"
#include "CondVariable.h"
#include "MutexException.h"

namespace advcpp
{

using std::tr1::shared_ptr;
template < class T,  template <typename , typename> class storage  >
void WaitableQueue<T,storage>::Enqueue(const T&  item) NOEXCEPT
{
    
    m_mutex.Lock();
    try
    {
        m_queue.push(item);
    }
    catch(std::exception& ex)
    {
        m_mutex.Unlock();
        throw;
    }
    
    
    
    
    try
    {
        m_mutex.Unlock();
    }
    catch(MutexException & ex)
    {
        //TODO
    }

   m_condVariable.CondSignal(); 
    
}
template < class T,  template <typename,typename > class storage  >
class Predicate
{
public:
    Predicate(WaitableQueue<T, storage>& queue):m_queue(queue){}
    bool operator()(void)
    {
        return !m_queue.Empty();
    } 
private:
    WaitableQueue<T, storage>&  m_queue;
};


template < class T,  template <typename,typename > class storage  >
T WaitableQueue<T, storage >::Dequeue(void) NOEXCEPT
{
    m_mutex.Lock();
   try
   {
        m_condVariable.CondWait(m_mutex, Predicate<T, storage>(*this));
   }
   catch(CondVariableException& ex )
   {
       m_mutex.Unlock();
   }
    
    T object;
    try
    {
        object = (m_queue.front());
    }
    catch(std::exception& ex)
    {
        m_mutex.Unlock();
        throw;
    }
    
    m_queue.pop();

    try
    {
        m_mutex.Unlock();
    }
    catch(MutexException & ex)
    {
        //TODO
    }

    return object;
}

template < class T,  template <typename,typename > class storage  >
size_t WaitableQueue<T,storage>::Size() NOEXCEPT
{
    Mutex m;
    m.Lock();
    size_t size = m_queue.size();
    try
    { 
        m.Unlock();
    }
    catch(MutexException& ex)
    {
        //TODO
    }
    //maybe race;
    return size;
}

template < class T,  template <typename,typename > class storage  >
bool WaitableQueue<T,storage>::Empty() NOEXCEPT
{
    Mutex m;
    m.Lock();
    bool empt = m_queue.empty();
    try
    {
        m.Unlock();
    }
    catch(MutexException& ex)
    {
        //TODO
    }
    //maybe race;
    return empt;
}

}