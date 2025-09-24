#include "csc/types.hpp"
#include "csc/action/ActionHub.hpp"
CSC_BEGIN

void ActionHub::makeActor(const ActProcessable &proable, const ActProcessor &process, const ScopeMetaData &meta, Livetime livetime){
    auto scopeid = meta.id;
    if(m_actors.find(scopeid) == m_actors.end()){
        m_actors.emplace(scopeid, ActorList());
    }

    auto pos = m_actors.find(scopeid);
    pos -> second.emplace_back(proable, process, scopeid, livetime);
}

void ActionHub::sendAction(ActionType type, std::any extraData, const ScopeMetaData &meta){
    m_actions.emplace_back(type, extraData, meta);
}

void ActionHub::sendInnerAction(std::any extraData, const ScopeMetaData &meta){
    m_actions.emplace_back(ActionType::Inner, extraData, meta);
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
    auto beg = m_actions.begin();
    auto end = m_actions.end();

    while(beg != end){
        if(beg -> type() == ActionType::Inner){
            ++beg;
            continue;
        }

        auto bak = context.postion();
        callActor(*beg);
        context.setPostion(bak);
        
        auto delpos = beg++;
        m_actions.erase(delpos);
    }
}

void ActionHub::processInnerAction(Context &context){
    auto beg = m_actions.begin();
    auto end = m_actions.end();

    while(beg != end){
        if(beg -> type() != ActionType::Inner){
            ++beg;
            continue;
        }

        do_processInnerAction(*beg);
        auto delpos = beg++;
        m_actions.erase(delpos);
    }
}

void ActionHub::do_processInnerAction(crAction action){
    switch(std::any_cast<InnerAction>(action.extraData())){
        case InnerAction::ExitScope:
            processExitScope(action);
            break;
    }
}

void ActionHub::processExitScope(crAction action){
    if(m_actors.find(action.scopeID()) == m_actors.end()) return;
    m_actors.erase(action.scopeID());
}

void ActionHub::callActor(crAction action){
    auto id = action.scopeID();
    auto &actors = m_actors.at(id);
    if(actors.size() == 0){
        return;
    }

    auto beg = actors.begin();
    auto end = actors.end();

    while(beg != end){
        if(!(beg -> processable(action))){
            ++beg;
            continue;
        }

        beg -> process(action);

        auto delpos = beg++;
        if(beg -> livetime() == Livetime::Oneshot){
            actors.erase(delpos);
        }
    }
}

CSC_END