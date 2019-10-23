#include "ConfigurationAgent.h"

namespace smartHome
{

ConfigurationAgent::ConfigurationAgent(const std::string & name,const std::string& type,const std::string& room, const std::string & floor,const std::string& log, const unordered_map<std::string, std::string>& config) NOEXCEPT
: m_name(name)
, m_room(room)
, m_floor(floor)
, m_type(type)
, m_libpath("./Lib/lib"+type + ".so")
, m_config(config)
, m_log(log)
{

}

const std::string& ConfigurationAgent::Name() const NOEXCEPT
{
    return m_name;
}

const std::string& ConfigurationAgent::Type() const NOEXCEPT
{
    return m_type;
}

const std::string& ConfigurationAgent::Libpath() const NOEXCEPT
{
    return m_libpath;
}

const std::string& ConfigurationAgent::Room() const NOEXCEPT
{
    return m_name;
}

const std::string& ConfigurationAgent::Floor() const NOEXCEPT
{
    return m_type;
}

const std::string& ConfigurationAgent::Log() const NOEXCEPT
{
    return m_log;
}

const unordered_map<std::string, std::string>& ConfigurationAgent::config() const NOEXCEPT
{
    return m_config;
}

bool operator==(const ConfigurationAgent& a, const ConfigurationAgent& b) NOEXCEPT
{
    return a.Name() == b.Name();
}

}