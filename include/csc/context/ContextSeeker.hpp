#ifndef CSC_CONTEXTSEEKER_HPP
#define CSC_CONTEXTSEEKER_HPP

#include "csc/context/types.hpp"
CSC_BEGIN

class ContextSeeker{
public:
    void enterScope(const CscStr &name);
    void leaveScope(const CscStr &name);
    void getVariable(const CscStr &name, const CscStr &value, ValueType type);
};

CSC_END
#endif