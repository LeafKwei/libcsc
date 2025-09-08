#ifndef CSC_EVENTSYSTEM_HPP
#define CSC_EVENTSYSTEM_HPP

#include <map>
#include <list>
#include "csc/event/EventCtl.hpp"
CSC_BEGIN

class EventSystem : public EventCtl{
public:
    using EventList = std::list<Event>;

public:
    EventSystem() =default;

    void process();
    void pushEvent(const Event &event, int priority=-1) override;
    void pushHandler(const EventHandler &handler,  int priority=-1) override;

private:
    EventList m_events;
};

CSC_END
#endif