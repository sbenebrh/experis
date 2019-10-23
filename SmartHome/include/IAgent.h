#ifndef IAGENT_H
#define IAGENT_H


#include "CommonRefs.h"


namespace smartHome
{
class ISubscribe;
class IEnQ;
class Location;
class LiveLogger;

class IAgent
{
public: 
    virtual bool init(shared_ptr<ISubscribe> , shared_ptr<IEnQ>,shared_ptr<LiveLogger>) = 0;
    virtual void Stop() = 0;
    virtual bool IsSensor() = 0;
    virtual bool IsControler() = 0;
    typedef shared_ptr<IAgent> (*deviceFunc)(const std::string&, const std::string& ,const std::string&, shared_ptr<Location>);
};

}


#endif