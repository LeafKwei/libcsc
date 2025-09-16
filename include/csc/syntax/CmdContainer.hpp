#ifndef CSC_CMDCONTAINER_HPP
#define CSC_CMDCONTAINER_HPP

#include "csc/csc.hpp"
#include "csc/syntax/node.hpp"
CSC_BEGIN

class CmdContainer{
public:
    using CmdPtr = CommandPtr;

public:
    void       addCommand(CmdPtr cmd); 
};

CSC_END
#endif