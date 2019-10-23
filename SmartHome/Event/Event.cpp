#include "/home/samuel/work/SmartHome/include/Event.h"
#include <iostream>
#include <time.h>

#include "/home/samuel/work/SmartHome/include/Location.h"


namespace smartHome
{


Event::Event(std::string type, shared_ptr<Location> pLocation, const std::string& time) NOEXCEPT
: m_type(type)
, m_location(pLocation)
, m_time(time)
{
    
}

Event::~Event()
{
    
}

const std::string& Event::Type() const NOEXCEPT
{
    return m_type;
}

const std::string&  Event::Time() const NOEXCEPT
{
    return m_time;
}

const std::string& Event::Room() const NOEXCEPT
{
    return m_location -> Room();
}


const std::string& Event::Floor() const NOEXCEPT
{
    return m_location ->Floor();
}

std::ostream& operator<< (std::ostream& os, const Event& event )
{
    os<< "Time: "<< event.Time();
    os<< "Type: "<< event.Type() << std::endl;
    os <<"Room: " << event.Room() << std::endl;
    os <<"Floor: " << event.Floor() << std::endl;

    return os ;
}

}