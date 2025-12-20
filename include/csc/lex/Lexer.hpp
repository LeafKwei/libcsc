#ifndef CSC_LEXER_HPP
#define CSC_LEXER_HPP

#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

class Lexer{
public:
    Lexer(const String &str);
    int         index() const noexcept;
    LxErrno readToken(TokenPool &pool);

private:
    CharMngr mngr_;
    PureLexer pure_;
};

CSC_END
#endif