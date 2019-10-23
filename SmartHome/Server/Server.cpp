#include "Server.h"


#include <vector>
#include <dlfcn.h>
#include <iterator>
#include <algorithm>

#include "Parser.h"
#include "ConfigurationAgent.h"
#include "SubRegistry.h"
#include "EventQueue.h"
#include "IpubImpl.h"
#include "SerialPub.h"
#include "EventPublisher.h"
#include "EventDispatcher.h"
#include "AgentsManager.h"
#include "IAgent.h"
#include "Mutex.h"
#include "LiveLogger.h"
#include "Event.h"
#include "Location.h"



namespace smartHome
{

Server::Server(const std::string& pathconfig)
: m_pathconfig(pathconfig)
{
    m_parser = shared_ptr<IParser>(new Parser(pathconfig));
}



Server::~Server()
{

    std::vector<shared_ptr<advcpp::Thread> >::iterator it =
                                    m_threadsDisp.begin();

    for(size_t i = 0; it != m_threadsDisp.end();++it ,++i)
    {
        (*it) -> Join();
    }
   m_pAgent.erase(m_pAgent.begin(), m_pAgent.end());
   
}


void Server::start()
{
    try
    {
        std::vector<ConfigurationAgent> configs = m_parser -> Parse();
        shared_ptr<SubRegistry> sub(new SubRegistry);
        enQ = shared_ptr<EventQueue>(new EventQueue);
        shared_ptr<IpubImpl> serialImpl(new SerialPub);
        shared_ptr<EventPublisher> evPub(new EventPublisher(sub, serialImpl));

        shared_ptr<LiveLogger> logger(LiveLogger::getInstance());
        m_manager = shared_ptr<AgentsManager>(new AgentsManager(configs, sub, enQ, m_pAgent,logger ));
        m_handlers =  m_manager -> start();
        CreateDispatcher(static_cast<size_t>(advcpp::Thread::Cpu_cores()), enQ, evPub);
    }
    catch(const std::exception& e)
    {
        return;
    }
    


}

template <typename T>
class Stop
{
public:

    void operator()(T& obj)
    {
        obj -> Stop();
       
    }
};

class StopSensor
{
public:
    void operator()(shared_ptr<IAgent>& obj)
    {
        if(obj -> IsSensor())
        {
            obj -> Stop();
        }
    }
};
class StopControler
{
public:
    void operator()(shared_ptr<IAgent>& obj)
    {
        if(obj -> IsControler()&& !(obj ->IsSensor()))
        {
            obj -> Stop();
        }
    }
};

void Server::stop()
{
    /*stop first sensors and after controlers*/
    std::for_each(m_pAgent.begin(), m_pAgent.end(), StopSensor());
    std::for_each(m_pAgent.begin(), m_pAgent.end(), StopControler());

    std::for_each(m_dispatchers.begin(), m_dispatchers.end(), Stop<shared_ptr< EventDispatcher> >());
    
    sendPoisonAppel();
    //zombies
   m_threadsDisp.erase(m_threadsDisp.begin(), m_threadsDisp.end());
    
}

void Server::CreateDispatcher(size_t numberOfDispatcher,shared_ptr<EventQueue> enQ, shared_ptr<EventPublisher> evPub)
{
    for(size_t i = 0; i < numberOfDispatcher; ++i)
    {
        shared_ptr<EventDispatcher> disp(new EventDispatcher(enQ, evPub));
        m_dispatchers.push_back(disp);
        shared_ptr<advcpp::Thread> t(new advcpp::Thread(disp));
        m_threadsDisp.push_back(t);
    }
}

void Server::sendPoisonAppel()
{
    size_t size = m_handlers.size();
    while(!enQ -> Empty());
    for (size_t i = 0; i <= size;++i)
    {
        enQ -> enQ(shared_ptr<Event>(new Event("", shared_ptr<Location> (new Location("", "")), "")));
    }
}

}