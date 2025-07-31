#include "dbc/lex/Lexer.hpp"
DBC_BEGIN

Lexer::Lexer(const Dstring &str) : 
    m_index(0), m_str(str)
{

}

Locator Lexer::locator() const{
    return Locator(m_str, m_index);
}

DBC_END