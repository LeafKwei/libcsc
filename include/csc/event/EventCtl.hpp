#ifndef CSC_EVENTCTL_HPP
#define CSC_EVENTCTL_HPP

#include "csc/event/EventHandler.hpp"
#include "csc/event/types.hpp"
CSC_BEGIN

class EventCtl{
public:
    virtual void pushEvent(const Event &event) =0;              /* Push an event to event list. */
    virtual void pushData(const HandlerData &data) =0;     /* Push a Handler data. System will use handler which is matched by type in the data to process event with the data. */
};

CSC_END
#endif