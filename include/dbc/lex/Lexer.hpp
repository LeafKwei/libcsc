#ifndef DBC_LEXCER_HPP
#define DBC_LEXCER_HPP

#include <map>
#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/lex/CharMngr.hpp"
#include "dbc/lex/Locator.hpp"
#include "dbc/lex/TokenReader.hpp"
#include "dbc/lex/PureLexer.hpp"
DBC_BEGIN

using ConverterBranches = std::map<Dstring, TokenType>;

class Lexer : public PureLexer{
public:
    Lexer();
    Lexer(const Dstring &str);
    Token nextToken();
    Locator locator() const;
    bool valid() const;
    const Dstring& str() const;

private:
    CharMngr m_mngr;
};

DBC_END
#endif