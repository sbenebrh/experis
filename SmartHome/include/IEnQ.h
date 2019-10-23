#ifndef IENQ_H
#define IENQ_H
#include "CommonRefs.h"

namespace smartHome
{

class Event;
class IEnQ
{
public:
virtual void enQ(shared_ptr<Event> e) NOEXCEPT = 0;
};

}



#endif
