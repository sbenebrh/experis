#ifndef IDeQ_H
#define IDeQ_H

#include<tr1/memory>

#include "event.h"


namespace preparation
{

class IDeQ
{
public:
    virtual std::tr1::shared_ptr<Event> deQ()  = 0;
    virtual bool Empty();
};
}

#endif