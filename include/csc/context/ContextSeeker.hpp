#ifndef CSC_CONTEXTSEEKER_HPP
#define CSC_CONTEXTSEEKER_HPP

#include "csc/context/types.hpp"
CSC_BEGIN

class ContextSeeker{
public:
    virtual ~ContextSeeker() =default;
    virtual void enterScope(const CscStr &name) =0;
    virtual void leaveScope(const CscStr &name) =0;
    virtual void getVariable(const CscStr &name, const CscStr &value, ValueType type) =0;
};

CSC_END
#endif