#include "AgentsManager.h"

#include <dlfcn.h>
#include <iterator>
#include <algorithm>
#include <stdexcept>
#include <iostream>

#include "ConfigurationAgent.h"
#include "IAgent.h"
#include "Location.h"
#include "ISubscribe.h"


namespace smartHome
{

AgentsManager::AgentsManager(std::vector<ConfigurationAgent>configs, shared_ptr<ISubscribe> psubscribe,shared_ptr<IEnQ> penQ,std::vector<shared_ptr<IAgent> >& pAgents,shared_ptr<LiveLogger> plogger ) NOEXCEPT
: m_agents(configs)
, m_psub(psubscribe)
, m_pAgent(pAgents)
, m_pEnQ(penQ)
, m_plogger(plogger)
{

}

class Closer
{
public:
    void operator()(void * obj)
    {
        dlclose(obj);
    }
};

AgentsManager::~AgentsManager()
{
     std::for_each(m_handlers.begin(),m_handlers.end(), Closer());
}
class UnknowSharedObjectException: public std::exception
{
public:
    UnknowSharedObjectException(std::string err){std::cout << err<<std::endl;}

};

class FactoryAgent
{
public:
    FactoryAgent(std::vector<shared_ptr<IAgent> >& Agents, std::vector<void* >& handlers ): m_pAgent(Agents), m_handlers(handlers){}
    void operator()(const ConfigurationAgent& obj)
    {
    try
    {
       void * handler= dlopen(obj.Libpath().c_str(), RTLD_LAZY);
       if(handler == NULL)
       {
           throw UnknowSharedObjectException( "not found " + obj.Libpath() );
       }
    
       IAgent::deviceFunc dev = (IAgent::deviceFunc) dlsym(handler, "Maker");
       if(dev == NULL)
       {
           throw UnknowSharedObjectException("not found Maker" + obj.Libpath());
       }
       
       
       shared_ptr<Location> pLocation(new Location(obj.Room(), obj.Floor()));
       shared_ptr<IAgent> device(dev(obj.Name(), obj.Type(), obj.Log(),pLocation));
       //safe zone
       m_handlers.push_back(handler);
       m_pAgent.insert(m_pAgent.end(), device);
       
    }
    catch(std::exception ex)
    {

    }
       
    }

private:
    std::vector<shared_ptr<IAgent> >& m_pAgent;
    std::vector<void* >& m_handlers;
   
};


class Configurator
{
public:
    Configurator(shared_ptr<ISubscribe> psub, shared_ptr<IEnQ> pEnQ,shared_ptr<LiveLogger> plogger):m_psub(psub), m_pEnQ(pEnQ), m_pLogger(plogger){}
    void operator()(shared_ptr<IAgent> obj)
    {
        obj ->init(m_psub, m_pEnQ, m_pLogger);
    }
private:
    shared_ptr<ISubscribe> m_psub;
    shared_ptr<IEnQ> m_pEnQ;
    shared_ptr<LiveLogger> m_pLogger;

};

std::vector<void* > AgentsManager::start() NOEXCEPT
{
    std::for_each(m_agents.begin(), m_agents.end(), FactoryAgent( m_pAgent, m_handlers));
    std::for_each(m_pAgent.begin(), m_pAgent.end(), Configurator(m_psub,m_pEnQ, m_plogger));
    return m_handlers;
}

}