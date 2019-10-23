#include <cassert>
#include "Thread.h"
#include "CreationFailureException.h"
#include "IRunnable.h"

#include <pthread.h>
#include <unistd.h>
#include <stdexcept>



namespace advcpp
{

Thread::Thread(std::tr1::shared_ptr<IRunnable> Run)
: needJoin(true)
, spRun(Run)
, flag(false)
{
    //static std::tr1::shared_ptr<IRunnable> run(Run);
   // run = Run;
    if(!Run)
    {
        throw std::invalid_argument("from Thread ctor");
    }
    int result = 0;
    if ((result = pthread_create(&m_id, 0,&work , &spRun)) != 0)
    {
        throw CreationFailureException(result);
    }
    
}

void * Thread::work(void * p)
{
    using std::tr1::shared_ptr;
    shared_ptr< IRunnable > runnableObj = *reinterpret_cast< shared_ptr< IRunnable >* >(p) ;
    try
    {
        (runnableObj) -> run();
    }
    catch(std::exception const& x)
    {
        std::cerr << x.what();
        assert(false);
    }
    catch(...)
    {
        std::cerr << "unknown error" << std::endl;
        assert(false); 
    }
    return 0;
}

Thread::~Thread()
{
    assert(!flag);
}

void Thread::Join()
{
    if (needJoin)
    {
        needJoin = false;
        int result = pthread_join(m_id, 0);
        if (result != 0)
        {
            throw CreationFailureException(result);
        }
        
        
        return;
    }
    assert(false);
}

void Thread::Detach()
{
    if(needJoin)
    {   
        needJoin = false;
        int result = 0;
        result = pthread_detach(m_id);

        if (result != 0)
        {
            throw CreationFailureException(result);
        }
        return ;
    }
    assert(false);
}

void Thread::Sleep(unsigned int sleeptime)
{
    while(usleep(sleeptime));
}

void Thread::Yield()
{
    int result = pthread_yield();
    if (result != 0)
    {
        throw CreationFailureException(result);
    }
}

int Thread::Cpu_cores()
{
    unsigned int eax=11,ebx=0,ecx=1,edx=0;

    asm volatile("cpuid"
        : "=a" (eax),
          "=b" (ebx),
          "=c" (ecx),
          "=d" (edx)
        : "0" (eax), "2" (ecx)
        : );

    return eax;
}

} // namespace advcpp