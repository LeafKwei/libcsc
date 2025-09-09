#include "csc/event/EventSystem.hpp"
CSC_BEGIN

void EventSystem::process(Context &context){

}

void EventSystem::pushEvent(const Event &event, int priority){
    if(priority == -1){
        m_events.push_back({priority, event.type, event.extraData});
        return;
    }

    auto begin = m_events.cbegin();
    auto end = m_events.cend();
    for(; begin != end; begin++){                //Compare priority then find a suitable postion.
        if(begin -> priority < priority){
            break;
        }
    }

    if(begin != end){                                   //If there is finding a postion.
        m_events.insert(begin, {priority, event.type, event.extraData});
        return;
    }

     //If this event's priority is the lowest.
    m_events.push_back({priority, event.type, event.extraData});
}

void EventSystem::pushHandler(const EventHandler &handler){

}



CSC_END