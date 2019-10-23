#ifndef FIRE_EVENT_H
#define FIRE_EVENT_H


#include "Event.h"
#include "CommonRefs.h"
namespace smartHome
{
class FireEvent:public Event
{
public:
    FireEvent(shared_ptr<Location> pLocation, std::string time) NOEXCEPT;
};

std::ostream& operator<< (std::ostream& os, const FireEvent& event );

}


#endif