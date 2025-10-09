#ifndef CSC_LEXCER_HPP
#define CSC_LEXCER_HPP

#include <map>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/types.hpp"
#include "csc/lex/types.hpp"
#include "csc/lex/CharMngr.hpp"
#include "csc/lex/Locator.hpp"
#include "csc/lex/TokenReader.hpp"
#include "csc/lex/PureLexer.hpp"
CSC_BEGIN

class Lexer{
public:
    Lexer();
    Lexer(crString str);
    LexResult nextToken();
    Locator    locator(int offset=0) const;
    bool         valid() const;
    crString    str() const;

private:
    PureLexer  m_pure;
    CharMngr m_mngr;
};

CSC_END
#endif