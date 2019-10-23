#ifndef WAITABLEQUEUE_H
#define WAITABLEQUEUE_H

#include "Mutex.h"
#include "CondVariable.h"

#include<queue>
#include<tr1/memory>

namespace advcpp
{
#define NOEXCEPT throw()

template < typename T,  template <typename ,typename S = std::deque<T> > class storage = std::queue  >
class WaitableQueue
{
public:

    void Enqueue(const T& item) NOEXCEPT;
    T  Dequeue(void) NOEXCEPT;

    size_t Size() NOEXCEPT;
    bool Empty() NOEXCEPT;

private:
    storage< T >  m_queue;
    Mutex m_mutex;
    CondVariable m_condVariable;
};

} // namespace advcpp

#include "WaitableQueue.hpp"


#endif
