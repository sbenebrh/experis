#ifndef SUB_REGISTRY_H
#define SUB_REGISTRY_H


#include "CommonRefs.h"

#include "ISubLookUp.h"
#include "ISubscribe.h"

namespace smartHome
{

class IEventHandler;
class EventCriterion;

class SubRegistry:public ISubLookup, public ISubscribe
{

public:
    virtual void add(shared_ptr<EventCriterion> criterion,shared_ptr<IEventHandler> );
//    virtual void remove(const EventCriterion&, shared_ptr<IEventHandler> );
    virtual std::set<shared_ptr<IEventHandler> > setLookUp(shared_ptr<Event> event); 

private:
    unordered_map<std::string,std::set<shared_ptr< IEventHandler> > > m_subscribers; 


};
}


#endif