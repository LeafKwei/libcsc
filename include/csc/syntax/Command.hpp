#ifndef CSC_COMMNAD_HPP
#define CSC_COMMNAD_HPP

#include <vector>
#include <memory>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/syntax/types.hpp"
CSC_BEGIN

class Command;
using CommandPtr = std::shared_ptr<Command>;
using CommandBranches = std::vector<CommandPtr>;

class Command{
public:
    virtual int tokenNumber() =0;
    virtual Policy run(const std::vector<Token> &tokens, Context &context) =0; 
};

CSC_END
#endif