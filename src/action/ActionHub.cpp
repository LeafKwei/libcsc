#include "csc/types.hpp"
#include "csc/action/ActionHub.hpp"
CSC_BEGIN

void ActionHub::sendAction(ActionType type, std::any extraData, const ScopeMetaData &meta){
    m_actions.emplace_back(type, extraData, meta);
}

void ActionHub::sendInnerAction(std::any extraData, const ScopeMetaData &meta){
    m_actions.emplace_back(ActionType::Inner, extraData, meta);
}

void ActionHub::addActor(ActProcessable checker, ActProcessor worker, UID scopeid, Livetime livetime){
    if(m_actors.find(scopeid) == m_actors.end()){
        m_actors.insert({scopeid, ActorList()});
    }

    m_actors.at(scopeid).emplace_back(checker, worker, livetime);
}

void ActionHub::distributeAction(Context &context){
    auto actionPtr = m_actions.begin();
    auto end = m_actions.end();

    while(actionPtr != end){
        switch(actionPtr -> type()){
            case ActionType::Inner:
                distributeInnerAction(*actionPtr, context);
                break;
            default:
                distributePublicAction(*actionPtr, context);
        }
        
        actionPtr = m_actions.erase(actionPtr);
    }
}

void ActionHub::distributePublicAction(crAction action, Context &context){
    auto actorListPtr = m_actors.find(action.scopeID());
    if(actorListPtr == m_actors.end()){
        return;
    }

    auto &actorList = actorListPtr -> second;
    auto actorPtr = findProcessableActor(actorList, action);
    if(actorPtr == actorList.end()){
        return;
    }

    /* 备份context当前的作用域位置，执行action后再恢复context的作用域 */
    auto backup = context.postion();
    actorPtr -> process(action, context);
    context.setPostion(backup);
}

void ActionHub::distributeInnerAction(crAction action, Context &context){
    switch(std::any_cast<InnerAction>(action.extraData())){
        case InnerAction::ExitScope:
            process_innerExitScope(action, context);
            break;
    }
}

void ActionHub::process_innerExitScope(crAction action, Context &context){
    removeActor(action.scopeID(), Livetime::Scoped);
}

ActionHub::ActIterator ActionHub::findProcessableActor(ActorList &actorList, crAction action){
    auto actorPtr = actorList.begin();
    auto end = actorList.end();

    while(actorPtr != end){
        if(actorPtr -> processable(action)){
            return actorPtr;
        }
    }

    return end;
}

void ActionHub::removeActor(UID scopeid, Livetime livetime){
    auto actorListPtr = m_actors.find(scopeid);
    if(actorListPtr == m_actors.end()){
        return;
    }

    auto &actorList = actorListPtr -> second;
    auto actorPtr = actorList.begin();
    auto end = actorList.end();

    while(actorPtr != end){
        if(actorPtr -> livetime() == livetime){
            actorPtr = actorList.erase(actorPtr);
        }
    }

    if(actorList.size() != 0){
        return;
    }

    m_actors.erase(scopeid);
}

CSC_END