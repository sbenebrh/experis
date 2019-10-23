#include "EventPublisher.h"
#include "ISubLookUp.h"
#include "IpubImpl.h"
#include "Event.h"

namespace smartHome
{

EventPublisher::EventPublisher(shared_ptr<ISubLookup> plookup, shared_ptr<IpubImpl> pPubImpl) NOEXCEPT
: m_plookup(plookup)
, m_pPubImpl(pPubImpl)
{
    
}

void  EventPublisher::publish(shared_ptr<Event> pEvent) NOEXCEPT
{
    try{
        std::set<shared_ptr<IEventHandler> > handlers = m_plookup -> setLookUp(pEvent);
        m_pPubImpl -> pub(pEvent, handlers.begin(), handlers.end());

    }
    catch(std::out_of_range& ex)
    {

    }
}
}