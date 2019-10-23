#ifndef FIRECONTROLER_H
#define FIRECONTROLER_H

#include "IAgent.h"
#include "LiveLogger.h"

namespace smartHome
{
class Location;
class ISubscribe;
class IEventHandler;
class CommonSensor;

class FireControler: public IAgent
{
public:
    FireControler(const std::string& name, const std::string& type, shared_ptr<Location> pLocation);

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