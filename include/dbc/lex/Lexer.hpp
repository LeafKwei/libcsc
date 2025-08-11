#ifndef DBC_LEXCER_HPP
#define DBC_LEXCER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/types.hpp"
#include "dbc/lex/CharMngr.hpp"
#include "dbc/lex/Locator.hpp"
DBC_BEGIN

class Lexer{
public:
    Lexer(const Dstring &str);
    Token nextToken();
    int index() const;
    Locator locator() const;
    void setAutoSkipBlank(bool b);

private:
    int m_index;
    CharMngr m_mngr;
    bool m_autoSkipBlank;
};

DBC_END
#endif