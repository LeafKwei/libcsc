#include "csc/types.hpp"
#include "csc/action/ActionHub.hpp"
CSC_BEGIN

void ActionHub::makeActor(const ActProcessable &proable, const ActProcessor &process, Livetime livetime=Livetime::Scoped, const Context &context){
    auto scopeid = context.scopeID();
    if(m_actors.find(scopeid) == m_actors.end()){
        m_actors.emplace(scopeid, ActorList());
    }

    auto pos = m_actors.find(scopeid);
    pos -> second.emplace_back(proable, process, scopeid, livetime);
}

void ActionHub::sendAction(ActionType type, std::any extraData, const Context &context){
    m_actions.emplace_back(type, extraData, context);
}

void ActionHub::sendInnerAction(std::any extraData, const Context &context){
    m_actions.emplace_back(ActionType::Inner, extraData, context);
}

Size_t ActionHub::threshold(){
    return m_threshold;
}

void ActionHub::setThreshold(int threshold){
    if(threshold < 1) throw ActionExcept("Threshold must be a postive number.");
    m_threshold = threshold;
}

Size_t ActionHub::sizeofActions(){
    return m_actions.size();
}

void ActionHub::distributeAction(Context &context){

}

void ActionHub::processInnerAction(Context &context){

}


CSC_END