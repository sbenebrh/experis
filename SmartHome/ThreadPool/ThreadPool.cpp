#include "ThreadPool.h"

namespace smartHome
{
    

ThreadPool::ThreadPool(size_t numOfThreads)
: m_Work(true)
{
    m_threads = std::list < shared_ptr<advcpp::Thread> >(numOfThreads);
}

ThreadPool::~ThreadPool()
{
    std::list < shared_ptr<advcpp::Thread> >::iterator it = 
                        m_threads.begin();
    for(; it != m_threads.end(); ++it)
        {
            (*it) -> Join() ;
        }
}

void ThreadPool::addTask(shared_ptr<IRunnable> run)
{
    m_tasks.Enqueue(run);
}

void ThreadPool::run()
{
    std::list < shared_ptr<advcpp::Thread> >::iterator it = 
                        m_threads.begin();
    while(m_Work)
    {
        for(; it != m_threads.end(); ++it)
        {
            *it = shared_ptr<advcpp::Thread>(new advcpp::Thread(m_tasks.Dequeue()));
        }
    }
}

void ThreadPool::SetOff()
{
    m_Work = false;
}


}