#include "LiveLogger.h"

#include <fstream>

namespace smartHome
{

LiveLogger* LiveLogger::m_log = 0;

LiveLogger* LiveLogger::getInstance()
{
    advcpp::Mutex m;
    m.Lock();
    if(m_log == 0)
    {
        m_log = new LiveLogger();
    }
    m.Unlock();
    return m_log;
}

void LiveLogger::Write(const std::string& filepath, const std::string& info)
{
    m_mutex.Lock();
    std::ofstream inFile(filepath);
    m_mutex.Unlock();

    inFile << info;
}

const std::string LiveLogger::Read(const std::string& filepath)
{
    m_mutex.Lock();
    std::ifstream onFile(filepath);
    m_mutex.Unlock();

    std::string info;
    onFile >> info;

    return info;
}

LiveLogger::LiveLogger()
{
    
}

void DestroyLog(LiveLogger* log)
{
    delete log;
}

}