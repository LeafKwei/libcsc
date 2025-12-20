#ifndef CSC_COMMAND_HPP
#define CSC_COMMAND_HPP

#include <vector>
#include <functional>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/action/ActionCtl.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

using OperandList    = std::vector<Operand>;
using CmdRunnable = std::function<bool(OperandList &operands)>;
using CmdRun          = std::function<void(OperandList &operands, Context &context, ActionCtl &ctl)>;

struct Command{
    String                key;
    CommandType type;
    CmdRunnable   runnable;
    CmdRun            run;
};

CSC_END
#endif