#ifndef IPUBIMPL_H
#define IPUBIMPL_H


#include "CommonRefs.h"
#include <set>

namespace smartHome
{
class Event;
class IEventHandler;

class IpubImpl
{
public:
    typedef std::set<shared_ptr<IEventHandler> >::iterator Iter;
    virtual void pub(shared_ptr<Event> pEvent, Iter beg, Iter end) = 0;
};
}


#endif