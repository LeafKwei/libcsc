#ifndef DBC_LEX_TYPES_HPP
#define DBC_LEX_TYPES_HPP

#include <cstdint>
#include "dbc/dbc.hpp"
#include "dbc/types.hpp"
DBC_BEGIN

typedef uint32_t EndingFlag;

enum class TokenType{
    Bad, None, 
    Identifier, Operator, Delimitor,
    Number, String, RawString
};

struct Token{
    TokenType type;
    Dstring buffer;
};

DBC_END
#endif