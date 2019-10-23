#ifndef EVENT_H
#define EVENT_H

#include <string>

#include "CommonRefs.h"

namespace smartHome
{
class Location;

class Event
{
public:
    Event(std::string type, shared_ptr<Location> pLocation, const std::string& time) NOEXCEPT;
    virtual ~Event();

    const std::string&  Time() const NOEXCEPT;
    const std::string& Type() const  NOEXCEPT;
    const std::string& Room() const NOEXCEPT;
    const std::string& Floor() const NOEXCEPT;


protected:
    std::string m_type ;
    shared_ptr<Location> m_location;
    std::string m_time;
};

std::ostream& operator<< (std::ostream& os, const Event& event );

}


#endif