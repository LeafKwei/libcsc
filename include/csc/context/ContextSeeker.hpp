#ifndef CSC_CONTEXTSEEKER_HPP
#define CSC_CONTEXTSEEKER_HPP

#include "csc/context/types.hpp"
#include "csc/context/VariableValues.hpp"
CSC_BEGIN

/**
 * ContextSeeker需要结合Context::iterate函数使用，用户可通过实现自己的ContextSeeker派生类从而实现自定义的
 * 对Context中的作用域和变量进行迭代的功能。
 */
class ContextSeeker{
public:
    virtual ~ContextSeeker() =default;
    virtual void enterScope(UID id, crString name) =0;
    virtual void leaveScope(UID id, crString name) =0;
    virtual void values(crString name, const VariableValues &values) =0;
};

CSC_END
#endif