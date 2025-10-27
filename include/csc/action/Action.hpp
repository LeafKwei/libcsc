#ifndef CSC_ACTION_HPP
#define CSC_ACTION_HPP

#include <functional>
#include "csc/action/types.hpp"
#include "csc/syntax/types.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

struct Action{
public:
    using OperandList    = std::vector<Operand>;
    using FuncRunnable = std::function<bool(CommandType type, const OperandList &operands, Context &context)>;
    using FuncRun          = std::function<bool(CommandType type, const OperandList &operands, Context &context)>;

public:
    FuncRunnable runnable;
    FuncRun          run;
};

CSC_END
#endif