#ifndef SMOKE_EVENT_H
#define SMOKE_EVENT_H

#include "/home/samuel/work/SmartHome/include/Event.h"
#include <iostream>

namespace smartHome
{

class IEnQ;

class SmokeEvent:public Event
{
public:
    SmokeEvent(shared_ptr<Location> pLocation,const std::string& time) NOEXCEPT;

};

std::ostream& operator<< (std::ostream& os, const SmokeEvent& event );
}


#endif