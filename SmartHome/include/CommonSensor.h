#ifndef COMMONSENSOR_H
#define COMMONSENSOR_H


#include "IRunnable.h"
#include "CommonRefs.h"

namespace smartHome
{

class Location;
class CommonSensor
{
public:
    CommonSensor(const std::string& name  , const std::string&, shared_ptr<Location>) NOEXCEPT;

    const std::string& name() const NOEXCEPT;
    const std::string& type() const NOEXCEPT;
    const unordered_map<std::string, std::string>& config() const NOEXCEPT;
    shared_ptr<Location> location() const NOEXCEPT;

private:
    std::string m_name; 
    std::string m_type;
    shared_ptr<Location> m_location;
    unordered_map <std::string, std::string> m_config;

};

}

#endif