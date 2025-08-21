#ifndef DBC_CONTEXT_HPP
#define DBC_CONTEXT_HPP

#include "dbc/context/types.hpp"
DBC_BEGIN

class Context{
public:
    

private:
    ScopePtr m_root;
    ScopePtr m_current;
};

DBC_END
#endif