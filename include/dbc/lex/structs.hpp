#ifndef DBC_LEX_STRUCTS_HPP
#define DBC_LEX_STRUCTS_HPP

#include "dbc/dbc.hpp"
#include "dbc/types.hpp"
DBC_BEGIN

struct Token{
    TokenType type;
    Dstring buffer;
};

DBC_END
#endif