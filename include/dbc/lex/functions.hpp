#ifndef DBC_FUNCTIONS_HPP
#define DBC_FUNCTIONS_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/lex/lex.hpp"

DBC_BEGIN

Option decide(DbcChar ch, TokenType charType, TokenType lastCharType, const DbcString &buffer) noexcept;


DBC_END
#endif