#ifndef IENQ_H
#define IENQ_H

#include <tr1/memory>
#include "event.h"

namespace preparation
{

class IEnQ
{
public:
    virtual void enQ(std::tr1::shared_ptr<Event> e) ;

};
}

#endif