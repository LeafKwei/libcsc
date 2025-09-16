#ifndef CSC_SYNTAX_TYPES_HPP
#define CSC_SYNTAX_TYPES_HPP

#include <vector>
#include "csc/csc.hpp"
CSC_BEGIN

enum class OperandType{
    Unexcepted,
    Identifier, Operator, Value, Values
};

CSC_END
#endif