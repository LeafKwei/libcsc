#ifndef CSC_TOKENREADER_HPP
#define CSC_TOKENREADER_HPP

#include <memory>
#include "csc/alias.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
CSC_BEGIN

class TokenReader{
public:
    virtual bool            readable(const CharMngr &mngr) const =0;
    virtual ReaderFlag read(Token &token) const =0;
};


using TokenReaderPtr = std::shared_ptr<TokenReader>;

CSC_END
#endif