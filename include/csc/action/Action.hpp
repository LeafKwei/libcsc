#ifndef CSC_ACTION_HPP
#define CSC_ACTION_HPP

#include <functional>
#include "csc/action/types.hpp"
#include "csc/syntax/types.hpp"
#include "csc/syntax/Operand.hpp"
CSC_BEGIN

struct Action{
public:
    using OperandList   = std::vector<Operand>;
    using ActRunnable = std::function<bool(CommandType type, const OperandList &operands, Context &context)>;
    using ActRun          = std::function<bool(CommandType type, const OperandList &operands, Context &context)>;

public:
    ActRunnable runnable;
    ActRun          run;
};

CSC_END
#endif