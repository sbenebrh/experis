#include "SerialPub.h"

#include <algorithm>
#include <iterator>
#include "IEventHandler.h"
#include "Event.h"
namespace smartHome
{
template<typename T>
class Handler
{
public:
    Handler(shared_ptr<Event> pEvent):m_pEvent(pEvent){}
    void operator()(T  obj)
    {
        obj -> HandlerEvent(m_pEvent);
    }
private:
    shared_ptr<Event> m_pEvent;
};

void SerialPub::pub(shared_ptr<Event> pEvent, Iter beg, Iter end) NOEXCEPT 
{
    std::for_each(beg, end, Handler<shared_ptr<IEventHandler> >(pEvent));
}

}