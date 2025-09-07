#ifndef CSC_EVENTHANDLER_HPP
#define CSC_EVENTHANDLER_HPP

#include <vector>
#include "csc/csc.hpp"
#include "csc/event/types.hpp"
#include "csc/context/Context.hpp"
CSC_BEGIN

class EventHandler{
public:
    using EventTypeList = std::vector<EventType>;
    using ConstTypeList = const EventTypeList&;

public:
    virtual int                    id() =0;
    virtual ConstTypeList typeofEvent() =0;
    virtual bool                isThisType(const Event &event) =0;
    virtual bool                discard() =0;
    virtual bool                event(const Event &event, Context &context) =0;
};

CSC_END
#endif