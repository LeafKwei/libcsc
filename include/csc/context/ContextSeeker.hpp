#ifndef CSC_CONTEXTSEEKER_HPP
#define CSC_CONTEXTSEEKER_HPP

#include "csc/context/types.hpp"
#include "csc/context/VariableValues.hpp"
CSC_BEGIN

class ContextSeeker{
public:
    virtual ~ContextSeeker() =default;
    virtual void enterScope(UID id, const CscStr &name) =0;
    virtual void leaveScope(UID id, const CscStr &name) =0;
    virtual void values(const CscStr &name, const VariableValues &values) =0;
};

CSC_END
#endif