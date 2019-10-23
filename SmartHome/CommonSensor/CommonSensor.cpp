#include "CommonSensor.h"

#include "Location.h"

namespace smartHome
{

CommonSensor::CommonSensor(const std::string& name  , const std::string& type , shared_ptr<Location> plocation) NOEXCEPT
: m_name(name)
, m_type(type)
, m_location(plocation)
{

}


const std::string& CommonSensor::name() const NOEXCEPT
{
    return m_name;
}

const std::string& CommonSensor::type() const NOEXCEPT
{
    return m_type;
}

const unordered_map<std::string, std::string>& CommonSensor::config() const NOEXCEPT
{
    return m_config;
}


shared_ptr<Location> CommonSensor::location() const NOEXCEPT
{
    return m_location;
}

}
