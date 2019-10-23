#ifndef THREAD_H
#define THREAD_H

#include <tr1/memory>
#include <pthread.h>

#include "NonCopyable.h"

namespace advcpp
{
class IRunnable;

class Thread:NonCopyable
{
public:
    Thread(std::tr1::shared_ptr<IRunnable> run);
    ~Thread();

    void Join();
    void Detach();

    static void Sleep(unsigned int);
    static void Yield();
    static int Cpu_cores();

private:
    static void* work(void *);

private:
    pthread_t m_id;
    bool needJoin;
    std::tr1::shared_ptr<IRunnable> spRun;
    bool flag;
};
}


#endif