#ifndef CSC_ACTION_HPP
#define CSC_ACTION_HPP

#include "csc/context/Context.hpp"
#include "csc/action/types.hpp"
CSC_BEGIN

class Action{
public:
    Action(ActionType type, std::any extraData, const Context &context) :
        m_type(type), m_extraData(extraData),
        m_pos(context.postion()), m_scopeid(context.scopeID()) {}

    ActionType                type() const noexcept { return m_type; }
    const std::any&         extraData() const noexcept { return m_extraData; }
    const Context::Pos&  postion() const noexcept { return m_pos; }         
    UID                            scopeID() const noexcept { return m_scopeid; }    

private:
    ActionType   m_type;
    std::any         m_extraData;
    Context::Pos m_pos;
    UID               m_scopeid;
};

CSC_END
#endif