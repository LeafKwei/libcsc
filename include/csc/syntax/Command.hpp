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

class Command{
public:
    using TokenList = std::vector<Token>;
    using ConstTokenList = const TokenList&;

public:
    virtual int tokenNumber() =0;
    virtual Policy run(ConstTokenList tokens, Context &context) =0; 
};

CSC_END
#endif