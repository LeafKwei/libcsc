#ifndef CSC_TOKENREADER_HPP
#define CSC_TOKENREADER_HPP

#include <memory>
#include "csc/alias.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

class TokenReader{
public:
    using Flag = ReaderFlag;

public:
    virtual bool readable(const CharMngr &mngr) const noexcept =0;
    virtual Flag read(CharMngr &mngr, TokenHolder &holder) =0;
};

using TokenReaderPtr = std::shared_ptr<TokenReader>;

CSC_END
#endif