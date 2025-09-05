#ifndef CSC_EVENTSYSTEM_HPP
#define CSC_EVENTSYSTEM_HPP

#include <map>
#include <vector>
#include "csc/event/EventCreator.hpp"
CSC_BEGIN

class EventSystem : public EventCreator{
public:
    using EventList = std::vector<Event>;

public:
    EventSystem() =default;

    void pushEvent(const Event &event) override;

private:
    EventList m_events;
};

CSC_END
#endif