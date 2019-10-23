#ifndef IDEQ_H
#define IDEQ_H

#include "CommonRefs.h"

namespace smartHome
{

class Event;

class IDeQ
{
public:
    virtual shared_ptr<Event> deQ() NOEXCEPT = 0;
    virtual bool Empty() = 0;
};

}



#endif
