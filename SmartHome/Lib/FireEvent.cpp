#include "FireEvent.h"
#include "Location.h"

namespace smartHome
{
FireEvent::FireEvent(shared_ptr<Location> pLocation, std::string time) NOEXCEPT
: Event("FIRE", pLocation, time)
{
    
}

std::ostream& operator<< (std::ostream& os, const FireEvent& event )
{
    os << static_cast<Event>(event);
    return os;
}
}