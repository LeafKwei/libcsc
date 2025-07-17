#ifndef DBC_TYPES_HPP
#define DBC_TYPES_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

enum class TokenType{Empty, Unknown, Blank, String, Operator};
enum class ErrorType{None, Unexcepted};

struct Derror{
    ErrorType type;
    Dstring message;
};

DBC_END
#endif