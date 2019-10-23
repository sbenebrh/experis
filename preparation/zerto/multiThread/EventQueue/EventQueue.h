#include "eventQueue.h"

#include <tr1/memory>

namespace preparation
{
EventQueue::EventQueue() NOEXCEPT
:m_pwaitableQ(new advcpp::WaitableQueue<std::tr1::shared_ptr < Event> >)

{
    
}

void EventQueue::enQ(std::tr1::shared_ptr<Event> e) NOEXCEPT
{
    m_pwaitableQ -> Enqueue(e);
}    


std::tr1::shared_ptr<Event> EventQueue::deQ() NOEXCEPT
{
    return m_pwaitableQ -> Dequeue();
}

bool EventQueue::Empty()
{
    return m_pwaitableQ -> Empty();
}
}