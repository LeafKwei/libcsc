#ifndef CSC_CONTEXTSEEKER_HPP
#define CSC_CONTEXTSEEKER_HPP

#include "csc/context/types.hpp"
#include "csc/context/Values.hpp"
CSC_BEGIN

class ContextSeeker{
public:
    virtual ~ContextSeeker() =default;
    virtual void enterScope(const CscStr &name) =0;
    virtual void leaveScope(const CscStr &name) =0;
    virtual void values(const CscStr &name, const Values &values) =0;
};

CSC_END
#endif