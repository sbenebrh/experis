#include "SmokeControler.h"
#include "Location.h"
#include "CommonSensor.h"
#include "EventCriterion.h"
#include "ISubscribe.h"
#include "SmokeHandler.h"

namespace smartHome
{

SmokeControler::SmokeControler(const std::string& name, const std::string& type, shared_ptr<Location> pLocation)
: m_pCommon(new CommonSensor( name ,type, pLocation))
{

}

bool SmokeControler::init(shared_ptr<ISubscribe> pSub, shared_ptr<IEnQ> pEnQ, shared_ptr<LiveLogger>)
{
    try
    {
        pSubscribe = pSub;
        pEventHAndler = shared_ptr<IEventHandler>(new SmokeHandler);
        shared_ptr<EventCriterion> pCriterion(new EventCriterion("SMOKE"));
        pSubscribe -> add(pCriterion, pEventHAndler);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
   
    
    return false;
}

void SmokeControler::Stop()
{
    
}

bool SmokeControler::IsSensor() 
{
    return false;
}
bool SmokeControler::IsControler()
{
    return true;
}

extern "C" shared_ptr<IAgent> Maker(const std::string& name, const std::string& type, const std::string& Log, shared_ptr<Location> pLocation )
{
    shared_ptr<IAgent> pAgent;
    try
    {
       pAgent = shared_ptr<IAgent>(new SmokeControler(name, type, pLocation));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return pAgent; 
}



}