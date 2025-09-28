#ifndef CSC_SYNTAX_TYPES_HPP
#define CSC_SYNTAX_TYPES_HPP

#include "csc/csc.hpp"
CSC_BEGIN

enum class OperandType{
    Unexcepted,
    Identifier, Keyword, Operator, Value, Values
};

struct Command;

CSC_END
#endif