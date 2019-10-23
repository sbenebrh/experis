#ifndef CONFIGURATION_AGENT_H
#define CONFIGURATION_AGENT_H

#include "CommonRefs.h"

namespace smartHome
{

class ConfigurationAgent
{
public:
    ConfigurationAgent(const std::string & m_name,const std::string& m_type, const std::string& room, const std::string & floor, const std::string& log,const unordered_map<std::string, std::string>& m_config) NOEXCEPT;

    const std::string& Name() const NOEXCEPT;
    const std::string& Type() const NOEXCEPT;
    const std::string& Libpath() const NOEXCEPT;
    const std::string& Room() const NOEXCEPT;
    const std::string& Floor() const NOEXCEPT;
    const std::string& Log() const NOEXCEPT;

    const unordered_map<std::string, std::string>& config() const NOEXCEPT;

private:
    std::string m_name;
    std::string m_room;
    std::string m_floor;
    std::string m_type;
    std::string m_libpath;
    std::string m_log;

    unordered_map<std::string, std::string> m_config;

};
bool operator==(const ConfigurationAgent& a, const ConfigurationAgent& b) NOEXCEPT;
}


#endif