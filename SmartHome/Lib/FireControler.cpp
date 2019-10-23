#include "FireControler.h"

#include <cassert>

#include "Location.h"
#include "CommonSensor.h"
#include "EventCriterion.h"
#include "ISubscribe.h"
#include "FireHandler.h"



namespace smartHome
{

FireControler::FireControler(const std::string& name, const std::string& type, shared_ptr<Location> pLocation)
: m_pCommon(new CommonSensor( name ,type, pLocation))
{

}

bool FireControler::init(shared_ptr<ISubscribe> pSub, shared_ptr<IEnQ> pEnQ,shared_ptr<LiveLogger> plogger)
{
    pSubscribe = pSub;
    try
    {
        pEventHAndler = shared_ptr<IEventHandler>(new FireHandler);
        shared_ptr<EventCriterion> pCriterion(new EventCriterion("FIRE"));
        pSubscribe -> add(pCriterion, pEventHAndler);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
    
    return false;
}

void FireControler::Stop()
{
    
}

bool FireControler::IsSensor() 
{
    return false;
}
bool FireControler::IsControler()
{
    return true;
}

extern "C" shared_ptr<IAgent> Maker(const std::string& name, const std::string& type,const std::string& log ,shared_ptr<Location> pLocation )
{
    try
    {
        shared_ptr<IAgent> pAgent(new FireControler(name, type, pLocation));
        return pAgent; 
    }
    catch(const std::exception& e)
    {
        assert(false and " error in allocation into firecontrolerMAker");
    }
    
    
}

}