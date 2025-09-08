#ifndef CSC_EVENTHANDLER_HPP
#define CSC_EVENTHANDLER_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/event/types.hpp"
#include "csc/context/Context.hpp"
CSC_BEGIN

class EventHandler{
public:
    virtual bool isThisType(const Event &event) =0;  //Check if this handler can be used to process the event.
    virtual bool discard() =0;                                       //Is this handler can be removed.
    virtual bool process(const Event &event, Context &context) =0; //Process event. If return true, the event will continue to be passed back.
};

CSC_END
#endif