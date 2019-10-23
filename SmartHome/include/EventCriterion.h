#ifndef EVENTCRITERION_H
#define EVENTCRITERION_H


#include "CommonRefs.h"
#include <set>

namespace smartHome
{
class Event;
class EventCriterion
{
public:
    EventCriterion(const std::string& event_type = "wildcard",const std::string& floor = "wildcard",const std::string& room = "wildcard") NOEXCEPT;
    const std::string& eventCriterion() const NOEXCEPT;

private:
    std::string m_criterion;

};

std::set<std::string> AllPossibilty(shared_ptr<Event> spEvent) NOEXCEPT;


}


#endif