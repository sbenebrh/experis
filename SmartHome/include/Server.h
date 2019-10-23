#ifndef SERVER_H
#define SERVER_H


#include <vector>

#include "CommonRefs.h"
#include "Thread.h"

namespace smartHome
{
class IParser;
class AgentsManager;
class EventQueue;
class EventPublisher;
class IAgent;
class EventDispatcher;

class Server
{


public:
    Server(const std::string& pathconfig);
    ~Server();
    void start();
    void stop();

private:
    void CreateDispatcher(size_t numberOfDispatcher,shared_ptr<EventQueue> enQ, shared_ptr<EventPublisher> evPub);
    void sendPoisonAppel();
private:
    std::string m_pathconfig;
    shared_ptr<IParser> m_parser;
    std::vector<shared_ptr<advcpp::Thread> > m_threadsDisp;
    std::vector<shared_ptr<IAgent> > m_pAgent;
    std::vector<shared_ptr< EventDispatcher> > m_dispatchers;
    shared_ptr<AgentsManager> m_manager;
    std::vector<void* > m_handlers;
    shared_ptr<EventQueue> enQ;

};

}
#endif
