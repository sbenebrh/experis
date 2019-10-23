#ifndef EVENT_H
#define EVENT_H


#include <string>
#include<thread>

#include "NonCopyable.h"

namespace preparation
{

class Event:advcpp::NonCopyable
{

public:
    Event(const std::string &,const std::thread::id& , bool isBlocked );



private:
    std::string m_message;
    std::thread::id m_threadID;
    bool m_isBlocked;   //for sync operation  


};
}

#endif