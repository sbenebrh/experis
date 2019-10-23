#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include <tr1/memory>

#include "WaitableQueue.h"
#include "IDeQ.h"
#include "IEnQ.h"

namespace preparation
{

class EventQueue:public IDeQ, public IEnQ
{
public:
    EventQueue() ;
    virtual void enQ(std::tr1::shared_ptr<Event> e) ;
    virtual std::tr1::shared_ptr<Event> deQ() ;
    virtual bool Empty();

private:
    std::tr1::shared_ptr< advcpp::WaitableQueue<std::tr1::shared_ptr<Event > > >m_pwaitableQ;
    
};

}


#endif