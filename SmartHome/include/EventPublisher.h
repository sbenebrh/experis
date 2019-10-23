#ifndef EVENTPUBLISHER_H
#define EVENTPUBLISHER_H

#include "CommonRefs.h"

namespace smartHome
{
class ISubLookup;
class IpubImpl;
class Event;

class EventPublisher
{
public:
    EventPublisher(shared_ptr<ISubLookup> plookup, shared_ptr<IpubImpl> pPubImpl) NOEXCEPT;
    void publish(shared_ptr<Event> pEvent) NOEXCEPT;

private:
    shared_ptr<ISubLookup> m_plookup;
    shared_ptr<IpubImpl> m_pPubImpl;

};
}

#endif