#ifndef CSC_EVENTSYSTEM_HPP
#define CSC_EVENTSYSTEM_HPP

#include <map>
#include <list>
#include <memory>
#include "csc/event/EventCtl.hpp"
CSC_BEGIN

class EventSystem : public EventCtl{
public:
    using EventList = std::list<Event>;
    using DataList = std::list<HandlerData>;
    using HandlerPtr = std::shared_ptr<EventHandler>;
    using HandlerList = std::vector<HandlerPtr>;

public:
    EventSystem() =default;

    void process(Context &context);

private:
    EventList m_events;
    DataList m_datas;
    HandlerList m_handlers;

    void installHandlers();
};

CSC_END
#endif