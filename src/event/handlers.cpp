
#include "csc/event/handlers.hpp"
CSC_BEGIN

//============== CommonHandler =============
CommonHandler::CommonHandler(InitEventTypes types) : m_types(types){}

bool CommonHandler::isThisType(const Event &event){
    for(auto &type : m_types){
        if(type == event.type) return true;
    }

    return false;
}

bool CommonHandler::process(Event &event, HandlerData &data,  Context &context){
    /* Do noting. */
}

//============== GenidxHandler =============
GenIdxHandler::GenIdxHandler(){

}

bool GenIdxHandler::process(Event &event, HandlerData &data,  Context &context){

}

CSC_END