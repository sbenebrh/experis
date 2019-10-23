#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H

#include "WaitableQueue.h"
#include "IDeQ.h"
#include "IEnQ.h"
namespace smartHome
{

class EventQueue:public IDeQ, public IEnQ
{
public:
    EventQueue() NOEXCEPT;
    virtual void enQ(shared_ptr<Event> e) NOEXCEPT;
    virtual shared_ptr<Event> deQ() NOEXCEPT;
    virtual bool Empty();

private:
    shared_ptr< advcpp::WaitableQueue<shared_ptr<Event > > >m_pwaitableQ;
    
};

}


#endif