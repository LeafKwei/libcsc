#ifndef CSC_SYNTAX_NODE_HPP
#define CSC_SYNTAX_NODE_HPP

#include <map>
#include <vector>
#include <memory>
#include "csc/csc.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

struct Command;
struct ContNode;
using CommandPtr = std::shared_ptr<Command>;
using ContNodePtr = std::shared_ptr<ContNode>;
using CommandList = std::vector<CommandPtr>;
using ContNodeMap = std::map<OperandType, ContNodePtr>;

struct ContNode{
    ContNodeMap nodes;
    CommandList commands;
};

CSC_END
#endif