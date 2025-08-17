#ifndef DBC_SYNTAX_TYPES_HPP
#define DBC_SYNTAX_TYPES_HPP

#include "dbc/dbc.hpp"
DBC_BEGIN

enum class Policy{Accepted, Missed, Bad};

enum class OperandType{
    Unexcepted,
    Identifier, Operator, Value
};

DBC_END
#endif