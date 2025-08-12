#ifndef DBC_LEX_TYPES_HPP
#define DBC_LEX_TYPES_HPP

#include <cstdint>
#include "dbc/dbc.hpp"
#include "dbc/types.hpp"
DBC_BEGIN

enum class TokenType{
    Aborted, Ignored, Unexcepted,
    Blank, Identifier, Operator, 
    Number, String, Array
};

struct Token{
    TokenType type;
    Dstring buffer;
};

DBC_END
#endif