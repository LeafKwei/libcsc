#ifndef CSC_SYNTAX_TYPES_HPP
#define CSC_SYNTAX_TYPES_HPP

#include "csc/csc.hpp"
CSC_BEGIN

enum class Policy{Accepted, Missed, Bad};

enum class OperandType{
    Unexcepted,
    Identifier, Operator, Value
};

CSC_END
#endif