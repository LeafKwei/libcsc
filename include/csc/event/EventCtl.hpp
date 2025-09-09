#ifndef CSC_EVENTCTL_HPP
#define CSC_EVENTCTL_HPP

#include "csc/event/EventHandler.hpp"
#include "csc/event/types.hpp"
CSC_BEGIN

class EventCtl{
public:
    virtual void pushEvent(const Event &event, int priority=-1) =0;     //Push an event to event list.
    virtual void pushHandler(const EventHandler &handler) =0;          //Push an event handler to handler list.
};

CSC_END
#endif