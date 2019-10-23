#include "Location.h"


namespace smartHome
{
Location::Location(const std::string& floor,const std::string& room) NOEXCEPT
: m_floor(floor)
, m_room(room)
{

}

const std::string& Location::Room() const NOEXCEPT
{
    return m_room;
}
const std::string& Location::Floor() const NOEXCEPT
{
    return m_floor;
}

}