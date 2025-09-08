#ifndef CSC_EVENT_HANDLERS_HPP
#define CSC_EVENT_HANDLERS_HPP

#include "csc/event/EventHandler.hpp"
CSC_BEGIN

class CommonEventHandler : public EventHandler{
public:
    using EventTypeList = std::vector<EventType>;
    using ConstTypeList = const EventTypeList&;

public:

private:
    EventTypeList m_typeList;
};

CSC_END
#endif