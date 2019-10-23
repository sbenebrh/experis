#include "EventDispatcher.h"

#include<iostream>

#include "EventPublisher.h"

namespace smartHome
{
EventDispatcher::EventDispatcher(shared_ptr<IDeQ> pDeQ, shared_ptr<EventPublisher> pPublish) NOEXCEPT
: m_pDeQ(pDeQ)
, m_publisher(pPublish)
, m_work(true)
{
    
}
void EventDispatcher::Stop()
{
    m_work = false;
}

void EventDispatcher::run()
{
    while(m_work && m_pDeQ -> Empty())
    {
        m_publisher -> publish(m_pDeQ -> deQ());
    }
    
}

}