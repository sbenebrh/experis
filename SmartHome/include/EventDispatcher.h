#ifndef EVENT_DISPATCHER_H
#define EVENT_DISPATCHER_H

#include "CommonRefs.h"
#include "IDeQ.h"
#include "IRunnable.h"

namespace smartHome
{

class EventPublisher;

class EventDispatcher:public advcpp::IRunnable
{
public:
    EventDispatcher(shared_ptr<IDeQ> pDeQ, shared_ptr<EventPublisher> pPublish) NOEXCEPT;
    void run();
    void Stop();
private:
    shared_ptr<IDeQ> m_pDeQ;
    shared_ptr<EventPublisher> m_publisher;
    bool m_work;


};
}


#endif
