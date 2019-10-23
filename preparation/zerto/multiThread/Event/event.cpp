

#include "event.h"


namespace preparation
{

Event::Event(const std::string & message,const std::thread::id& threadID , bool isBlocked )
: m_message(message)
, m_threadID(threadID)
, m_isBlocked(isBlocked)
{

}


}