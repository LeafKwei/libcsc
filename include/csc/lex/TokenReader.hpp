#ifndef CSC_TOKENREADER_HPP
#define CSC_TOKENREADER_HPP

#include <map>
#include <memory>
#include "csc/alias.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
CSC_BEGIN

class TokenReader{
public:
    using Result = std::pair<ReaderFlag, Token>;

public:
    virtual bool    readable(const CharMngr &mngr) =0;
    virtual Result  read(Token &token) =0;
};

using TokenReaderPtr = std::shared_ptr<TokenReader>;

CSC_END
#endif