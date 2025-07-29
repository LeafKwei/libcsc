#ifndef DBC_LEXCER_HPP
#define DBC_LEXCER_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
#include "dbc/types.hpp"
#include "dbc/lex/Locator.hpp"
DBC_BEGIN

class Lexer{
public:
    Lexer(const Dstring &str);

    
    Locator locator() const noexcept;

private:
    int m_index;
    const Dstring m_str;
};

DBC_END
#endif