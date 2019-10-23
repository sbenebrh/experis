#ifndef IEVENTHANDLER_H
#define IEVENTHANDLER_H


#include "CommonRefs.h"

namespace smartHome
{
class Event;
class IEventHandler
{
public:
    virtual void HandlerEvent(shared_ptr<Event> pEvent) = 0; 
};
}


#endif