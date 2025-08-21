#ifndef DBC_COMMNAD_HPP
#define DBC_COMMNAD_HPP

#include <vector>
#include <memory>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/context/Context.hpp"
#include "dbc/syntax/types.hpp"
DBC_BEGIN

class Command;
using CommandPtr = std::shared_ptr<Command>;
using CommandBranches = std::vector<CommandPtr>;

class Command{
public:
    virtual int tokenNumber() =0;
    virtual Policy run(const std::vector<Token> &tokens, Context &context) =0; 
};

DBC_END
#endif