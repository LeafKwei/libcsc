#ifndef CSC_ACTION_HPP
#define CSC_ACTION_HPP

#include "csc/context/Context.hpp"
#include "csc/action/types.hpp"
CSC_BEGIN

class Action{
public:
    Action(ActionType type, Any extraData, Context::crScpMeta meta) : 
        m_type(type), m_extraData(extraData),
        m_pos{meta.ptr}, m_scopeid(meta.id) {}

    ActionType                type() const noexcept          { return m_type; }
    const Any&               extraData() const noexcept { return m_extraData; }
    const Context::Pos&  postion() const noexcept    { return m_pos; }         
    UID                            scopeID() const noexcept   { return m_scopeid; }    

private:
    ActionType   m_type;
    Any              m_extraData;
    Context::Pos m_pos;
    UID               m_scopeid;
};

CSC_END
#endif