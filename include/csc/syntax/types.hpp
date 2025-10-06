#ifndef CSC_SYNTAX_TYPES_HPP
#define CSC_SYNTAX_TYPES_HPP

#include "csc/csc.hpp"
#include "csc/lex/types.hpp"
CSC_BEGIN

enum class OperandType{
    Unexcepted,
    Identifier, Keyword, Operator, Value, Values
};

struct Operand{
    String              str;
    TokenType      tp_tk;
    OperandType tp_op;
    ValueType       tp_va;
};

struct Command;

CSC_END
#endif