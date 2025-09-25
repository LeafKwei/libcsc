#include "csc/types.hpp"
#include "csc/action/ActionHub.hpp"
CSC_BEGIN

void ActionHub::sendAction(ActionType type, std::any extraData, const ScopeMetaData &meta){
    m_actions.emplace_back(type, extraData, meta);
}

void ActionHub::sendInnerAction(std::any extraData, const ScopeMetaData &meta){
    m_actions.emplace_back(ActionType::Inner, extraData, meta);
}

Size_t ActionHub::sizeofActions(){
    return m_actions.size();
}

void ActionHub::distributeAction(Context &context){
    auto beg = m_actions.begin();
    auto end = m_actions.end();

    while(beg != end){
        if(beg -> type() == ActionType::Inner) {++beg; continue;}
        std::cout << "type: " << static_cast<int>(beg -> type()) << ", id: " << beg ->scopeID() << ", extra: " <<  std::any_cast<String>(beg -> extraData()) << std::endl;
        beg = m_actions.erase(beg);
    }
}

void ActionHub::processInnerAction(Context &context){

}


CSC_END