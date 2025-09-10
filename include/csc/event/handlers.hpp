#ifndef CSC_EVENT_HANDLERS_HPP
#define CSC_EVENT_HANDLERS_HPP

#include "csc/event/EventHandler.hpp"
CSC_BEGIN

class CommonHandler : public EventHandler{
public:
    using EventTypeList = std::vector<EventType>;
    using ConstTypeList = const EventTypeList&;
    using InitEventTypes = std::initializer_list<EventType>;

public:
    CommonHandler() =default;
    CommonHandler(InitEventTypes types);
    bool isThisType(const Event &event) override;
    bool process(Event &event, HandlerData &data,  Context &context) override;

private:
    EventTypeList m_types;  /* Which event can be processed by this handler. */
};

class GenIdxHandler : public EventHandler{
public:
    GenIdxHandler();
    bool process(Event &event, HandlerData &data,  Context &context) override;
};

CSC_END
#endif