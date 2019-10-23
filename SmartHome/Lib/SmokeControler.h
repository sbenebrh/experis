#ifndef SMOKECONTROLER_H
#define SMOKECONTROLER_H

#include "IAgent.h"


namespace smartHome
{
class Location;
class ISubscribe;
class IEventHandler;
class CommonSensor;

class SmokeControler: public IAgent
{
public:
    SmokeControler(const std::string& name, const std::string& type, shared_ptr<Location> pLocation);

private:
    virtual bool init(shared_ptr<ISubscribe> , shared_ptr<IEnQ>,shared_ptr<LiveLogger>);
    virtual void Stop();
    virtual bool IsSensor() ;
    virtual bool IsControler() ;

protected:
    shared_ptr<ISubscribe> pSubscribe;
    shared_ptr<IEventHandler> pEventHAndler;
    shared_ptr<CommonSensor> m_pCommon;
};
}

#endif