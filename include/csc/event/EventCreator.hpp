#ifndef CSC_EVENTCREATOR_HPP
#define CSC_EVENTCREATOR_HPP

#include "csc/event/types.hpp"
CSC_BEGIN

class EventCreator{
public:
    virtual void pushEvent(const Event &event) =0;
};

CSC_END
#endif