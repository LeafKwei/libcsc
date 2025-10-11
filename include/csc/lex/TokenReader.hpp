#ifndef CSC_TOKENREADER_HPP
#define CSC_TOKENREADER_HPP

#include <vector>
#include <memory>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
CSC_BEGIN

class TokenReader;
using ReaderPtr = std::shared_ptr<TokenReader>;

class TokenReader{
public:
    virtual bool           readable(CharMngr &mngr) =0;
    virtual Token         read(CharMngr &mngr) =0;
    virtual TokenType type() =0;
};

CSC_END
#endif