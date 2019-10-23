#ifndef AGENTS_MANAGER_H
#define AGENTS_MANGER_H

#include <set>
#include <vector>

#include "CommonRefs.h"
#include "LiveLogger.h"

namespace smartHome
{

class ConfigurationAgent;
class ISubscribe;
class IEnQ;
class IAgent;
class UnknowSharedObjectException;

class AgentsManager
{
public:
    AgentsManager(std::vector<ConfigurationAgent>, shared_ptr<ISubscribe> psubcribe,shared_ptr<IEnQ> penQ, std::vector<shared_ptr<IAgent> >& pAgents, shared_ptr<LiveLogger> ) NOEXCEPT;
    ~AgentsManager();
    std::vector<void* > start() NOEXCEPT ;
    void shutdown() NOEXCEPT;

private:
    

private:
    std::vector<ConfigurationAgent> m_agents;
    shared_ptr<ISubscribe> m_psub;
    shared_ptr<IEnQ> m_pEnQ;
    std::vector<shared_ptr<IAgent> >& m_pAgent;
    std::vector<void* > m_handlers;
    shared_ptr<LiveLogger> m_plogger;

};

}

#endif
