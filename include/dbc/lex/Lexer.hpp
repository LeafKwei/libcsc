#ifndef DBC_LEXCER_HPP
#define DBC_LEXCER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/lex/Locator.hpp"
DBC_BEGIN

class Lexer{
public:
    Lexer(const Dstring &str);
    Token readNext(TokenType type);
    int index() const;
    Locator locator() const;

private:
    int m_index;
    const Dstring m_str;
    Dstring m_custom;
};

DBC_END
#endif