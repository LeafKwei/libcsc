#ifndef DBC_TYPES_HPP
#define DBC_TYPES_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

enum class TokenType{
    Empty, Unknown, Blank, 
    Identifier, Number, String, 
    LongString, Operator, Delimitor
};

enum class ErrorType{
    OK, Unexcepted, NoSuch, 
    Denied
};

struct Derror{
    ErrorType type;
    Dstring message;
};

DBC_END
#endif