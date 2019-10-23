#include "EventCriterion.h"

#include <cassert>

#include "Event.h"
#include "Location.h"

namespace smartHome
{
EventCriterion::EventCriterion(const std::string& event_type,const std::string& floor,const std::string& room ) NOEXCEPT
{
    m_criterion = event_type;
    m_criterion.append("_");
    m_criterion.append(floor);
    m_criterion.append("_");
    m_criterion.append(room);
}

const std::string& EventCriterion::eventCriterion() const NOEXCEPT
{
    return m_criterion;
}

std::set<std::string> AllPossibilty(shared_ptr<Event> spEvent) NOEXCEPT
{
    std::set<std::string> result;
    result.insert("wildcard_wildcard_wildcard");
    const std::string& room = spEvent ->Room() ;
    const std::string& floor = spEvent -> Floor() ;
    result.insert(spEvent ->Type()+"_" +room+"_"+ "floor");

    result.insert(spEvent->Type()+"_"+"wildcard" +"_"+"wildcard");
    result.insert(spEvent->Type()+"_"+room +"_"+"wildcard");
    result.insert(spEvent->Type()+"_"+"wildcard" +"_"+floor);
    result.insert("wildcard_wildcard_" + floor);
    result.insert("wildcard_" +room+ "_wildcard");
    result.insert("wildcard_"+ room+ "_"+ floor);
    assert(result.size() == 8);

    return result;
}

}