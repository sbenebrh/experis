#include "SubRegistry.h"

#include <stdexcept>
#include <algorithm>
#include <iterator>

#include "EventCriterion.h"

namespace smartHome
{

void SubRegistry::add(const shared_ptr<EventCriterion> criterion,shared_ptr<IEventHandler> eventHandler )
{
    m_subscribers[criterion->eventCriterion()].insert(eventHandler);
}


template<typename T>
class Inserter
{
public:
    Inserter(std::set<shared_ptr<IEventHandler> >& handlers,
                            const unordered_map<std::string, std::set<shared_ptr< IEventHandler> > >& indexbyCrit)
    : m_handlers(handlers)
    , m_indexbyCrit(indexbyCrit)
    {
    }
    void operator()(T obj)
    {
        unordered_map<std::string, std::set<shared_ptr< IEventHandler> > >::const_iterator it =
                            m_indexbyCrit.find(obj);
        if(it != m_indexbyCrit.end())
        {
            m_handlers.insert(it -> second.begin(), it ->second.end());
        }
    }
private:
    std::set<shared_ptr<IEventHandler> >& m_handlers;
    const unordered_map<std::string, std::set<shared_ptr< IEventHandler> > >& m_indexbyCrit;
};


std::set<shared_ptr<IEventHandler> > SubRegistry::setLookUp(shared_ptr<Event> event)
{
    std::set<std::string> criterions = AllPossibilty(event);
    std::set<shared_ptr<IEventHandler> > handlers;

    std::for_each(criterions.begin(), criterions.end(), Inserter<std::string>(handlers, m_subscribers));

    return handlers;

}
}