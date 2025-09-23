#ifndef CSC_CONTEXTER_HPP
#define CSC_CONTEXTER_HPP

#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

class Contexter{
public:
    using Pos = ScopePos;                                                                                                                                                                                                                                                                                                                                                                      

public:
    virtual ConstStr scopeName() const noexcept =0;
    virtual UID         scopeID() const noexcept =0;                 
    virtual Pos         postion() const =0;
};

CSC_END
#endif