#ifndef CSC_CMDCONTAINER_HPP
#define CSC_CMDCONTAINER_HPP

#include <iostream>
#include <csc/alias.hpp>
#include "csc/csc.hpp"
#include "csc/syntax/node.hpp"
CSC_BEGIN

class CmdContainer{
public:
    using CmdPtr = CommandPtr;
    using NodePtr = ContNodePtr;

public:
    CmdContainer();
    CmdContainer(const CmdContainer &other) =delete;
    CmdContainer& operator=(const CmdContainer &other) =delete;

    void addCommand(CmdPtr cmd);

private:
    NodePtr m_root;

    void do_addCommand(NodePtr node, CmdPtr cmd, Size_t opidx);
};

CSC_END
#endif