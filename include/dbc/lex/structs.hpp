#ifndef DBC_STRUCTS_HPP
#define DBC_STRUCTS_HPP

#include "dbc/dbc.hpp"
#include "dbc/types.hpp"
DBC_BEGIN

struct Locator{
    int index;
    int row;
    int col;
};

struct Token{
    TokenType type;
    DbcString buffer;
};

DBC_END
#endif