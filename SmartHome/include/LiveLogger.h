#ifndef LIVELOGGER_H
#define LIVELOGGER_H

#include "/home/samuel/work/SmartHome/include/NonCopyable.h"
#include "Mutex.h"

#include <fstream>

namespace smartHome
{

class LiveLogger:advcpp::NonCopyable
{

public: 
    static LiveLogger* getInstance();
    void Write(const std::string& filepath, const std::string& info);
    const std::string Read(const std::string& filepath);

private: 
    LiveLogger();
private:
    advcpp::Mutex m_mutex;
    static LiveLogger* m_log;
};

void DestroyLog(LiveLogger* log);
}


#endif