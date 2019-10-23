#ifndef ISUBSCRIBE_H
#define ISUBSCRIBE_H

#include "CommonRefs.h"

namespace smartHome
{
class IEventHandler;
class Event;
class EventCriterion;

class ISubscribe
{
public:
    virtual void add(shared_ptr<EventCriterion> criterion,shared_ptr<IEventHandler> ) = 0;
  //  virtual void remove(const EventCriterion&, shared_ptr<IEventHandler> ) = 0; // not event but event criterion
};
}

#endif