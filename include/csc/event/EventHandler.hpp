#ifndef CSC_EVENTHANDLER_HPP
#define CSC_EVENTHANDLER_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/event/types.hpp"
#include "csc/context/Context.hpp"
CSC_BEGIN

class EventHandler{
public:
    virtual bool isThisType(const Event &event) =0;  /* Check if this handler can be used to process the event. */
    virtual bool process(Event &event, HandlerData &data,  Context &context) =0; /* Process event. If return false, the event will continue to be passed. */
};

CSC_END
#endif