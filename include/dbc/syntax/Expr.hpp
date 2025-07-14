#ifndef DBC_EXPR_HPP
#define DBC_EXPR_HPP

#include <vector>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/structs.hpp"
#include "dbc/lex/LexHelper.hpp"

DBC_BEGIN

class Expr{
public:
    bool execute(const DbcString &raw, LexHelper &helper) const noexcept;
    bool execute(const DbcString &raw, LexHelper &helper, DbcPair &pair) const noexcept;
};


DBC_END
#endif