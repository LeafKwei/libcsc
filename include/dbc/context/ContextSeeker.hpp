#ifndef DBC_CONTEXTSEEKER_HPP
#define DBC_CONTEXTSEEKER_HPP

#include "dbc/context/types.hpp"
DBC_BEGIN

class ContextSeeker{
public:
    void enterScope(const Dstring &name);
    void leaveScope(const Dstring &name);
    void getVariable(const Dstring &name, const Dstring &value, ValueType type);
};

DBC_END
#endif