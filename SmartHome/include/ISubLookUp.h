#ifndef ISUBLOOKUP
#define ISUBLOOKUP

#include <set>

#include "CommonRefs.h"
namespace smartHome
{
class Event;
class IEventHandler;

class ISubLookup
{
public:
    virtual std::set<shared_ptr<IEventHandler> > setLookUp(shared_ptr<Event> event) = 0; 
};
}


#endif