#include "EventQueue.h"
#include "WaitableQueue.h"

namespace smartHome
{

EventQueue::EventQueue() NOEXCEPT
:m_pwaitableQ(new advcpp::WaitableQueue<shared_ptr < Event> >)

{
    
}

void EventQueue::enQ(shared_ptr<Event> e) NOEXCEPT
{
    m_pwaitableQ -> Enqueue(e);
}    


shared_ptr<Event> EventQueue::deQ() NOEXCEPT
{
    return m_pwaitableQ -> Dequeue();
}

bool EventQueue::Empty()
{
    return m_pwaitableQ -> Empty();
}
}