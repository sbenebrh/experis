#ifndef THREADPOOL_H
#define THREADPOOL_H


#include <list>

#include "Thread.h"
#include "CommonRefs.h"
#include "WaitableQueue.h"
#include "IRunnable.h"

namespace smartHome
{

class ThreadPool:public advcpp::IRunnable
{
public:
    ThreadPool(size_t numOfThreads);
    ~ThreadPool();
    void addTask(shared_ptr<IRunnable> run);
    virtual void run();
    void SetOff();

private:
    std::list<shared_ptr<advcpp::Thread> > m_threads;
    advcpp::WaitableQueue<shared_ptr<advcpp::IRunnable> > m_tasks;
    bool m_Work;

};
}


#endif