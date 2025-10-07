#ifndef CSC_SYNTAX_TYPES_HPP
#define CSC_SYNTAX_TYPES_HPP

#include "csc/csc.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

enum class OperandType{
    Unknown,
    Identifier, Keyword, Operator, Value, Values
};

struct Operand{
    Token              token;
    OperandType  type;
};

struct Command;

CSC_END
#endif