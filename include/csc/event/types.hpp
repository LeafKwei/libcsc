#ifndef CSC_EVENT_TYPES_HPP
#define CSC_EVENT_TYPES_HPP

#include <any>
#include "csc/csc.hpp"
CSC_BEGIN

enum class EventType{
    EnterScope, LeaveScope, MakeVariable
};

enum class HandlerType{
    Action_genidx
};

struct Event{
    EventType type;
    std::any extraData;
};

struct HandlerData{
    bool discarded;
    HandlerType type;
    std::any extraData;
};

CSC_END
#endif