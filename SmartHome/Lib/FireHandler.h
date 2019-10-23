#ifndef FIREHANDLER_H
#define FIREHANDLER_H

#include <iostream>

#include "IEventHandler.h"
#include "Event.h"

namespace smartHome
{

class FireHandler:public IEventHandler
{
public:
    virtual void HandlerEvent(shared_ptr<Event> pEvent) NOEXCEPT{ std::cout <<*pEvent.get() << std::endl;};

};
}

#endif
