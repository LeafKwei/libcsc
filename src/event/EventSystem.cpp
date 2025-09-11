#include "csc/event/EventSystem.hpp"
#include "csc/event/handlers.hpp"
CSC_BEGIN

void EventSystem::process(Context &context){

}

void EventSystem::pushEvent(const Event &event){
    m_events.push_back(event);
}

void EventSystem::pushData(const HandlerData &data){
    m_datas.push_back(data);
}

void EventSystem::installHandlers(){
    m_handlers.push_back(std::make_shared<GenIdxHandler>());
}

CSC_END