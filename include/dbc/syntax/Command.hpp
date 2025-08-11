#ifndef DBC_COMMNAD_HPP
#define DBC_COMMNAD_HPP

#include <vector>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/core/Dcontext.hpp"
DBC_BEGIN

class Command{
public:
    Derror run(const std::vector<Token> &tokens, Dcontext &context);
};

DBC_END
#endif