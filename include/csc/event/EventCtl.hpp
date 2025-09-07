#ifndef CSC_EVENTCTL_HPP
#define CSC_EVENTCTL_HPP

#include "csc/event/EventHandler.hpp"
#include "csc/event/types.hpp"
CSC_BEGIN

class EventCtl{
public:
    virtual bool hasEvent(EventType type) =0;                                                         //Check if event which is matched type exists.
    virtual bool hasHandler(int id) =0;                                                                     //Check if handler which is matched id exists.
    virtual void pushEvent(const Event &event, int priority=-1) =0;                       //Push an event to event list.
    virtual void pushHandler(const EventHandler &handler,  int priority=-1) =0;  //Push an event handler to handler list.
    virtual int    removeEvent(EventType type) =0;                                                  //Remove event. Return number of removed event.
    virtual int    removeHandler(int id) =0;                                                              //Remove handler from handler list if id is matched. Return number of removed handler.
};

CSC_END
#endif