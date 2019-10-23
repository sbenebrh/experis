#ifndef SMOKEHANDLER_H
#define SMOKEHANDLER_H

#include <iostream>

#include "IEventHandler.h"
#include "Event.h"

namespace smartHome
{

class SmokeHandler:public IEventHandler
{
public:
    virtual void HandlerEvent(shared_ptr<Event> pEvent) NOEXCEPT{ std::cout << (*pEvent) << std::endl;};
};
}


#endif