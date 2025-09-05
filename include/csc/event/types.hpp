#ifndef CSC_EVENT_TYPES_HPP
#define CSC_EVENT_TYPES_HPP

#include <any>
#include "csc/csc.hpp"
CSC_BEGIN

enum class EventType{
    EnterScope, LeaveScope, MakeVariable
};

struct Event{
    EventType type;
    std::any extraData;
};

CSC_END
#endif