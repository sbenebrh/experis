#include "logger.h"

#include <thread>
#include <mutex>

namespace preparation
{

std::tr1::shared_ptr<Logger> Logger::m_logger ;

std::tr1::shared_ptr<Logger> Logger::GetInstance(const std::istream& ifstm)
{
    std::mutex mu;
    mu.lock();
    if(m_logger == NULL)
    {
        m_logger = std::tr1::shared_ptr<Logger>(new Logger(ifstm));
       
    }
    mu.unlock();
    
    return m_logger;
}

Logger::Logger(const std::istream& ifstm)
: m_whereToWrite(ifstm)
{

}

void Logger::AsyncLog(const std::string& message) const
{

    std::thread t(/*TODO*/);
}
}