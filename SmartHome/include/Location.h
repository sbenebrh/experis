#ifndef LOCATION_H
#define LOCATION_H

#include "CommonRefs.h"

namespace smartHome
{

class Location
{
public:
    Location(const std::string& floor,const std::string& room) NOEXCEPT;
    
    const std::string& Room() const NOEXCEPT;
    const std::string& Floor() const NOEXCEPT;

private:
    std::string m_floor;
    std::string m_room;

};
}


#endif