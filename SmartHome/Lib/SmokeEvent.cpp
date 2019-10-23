#include "SmokeEvent.h"
#include "Location.h"

namespace smartHome
{
SmokeEvent::SmokeEvent(shared_ptr<Location> plocation, const std::string& time) NOEXCEPT
: Event("SMOKE", plocation, time)
{
    
}

std::ostream& operator<< (std::ostream& os, const SmokeEvent& event )
{
    os << static_cast<Event>(event);
    return os;
}
}