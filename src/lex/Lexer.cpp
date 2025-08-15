#include "dbc/lex/Lexer.hpp"
#include "dbc/lex/readers.hpp"
DBC_BEGIN

Lexer::Lexer() : Lexer(""){ }
Lexer::Lexer(const Dstring &str) : m_mngr(str){ }

Token Lexer::nextToken(){
    return nextTokenFrom(m_mngr);
}

bool Lexer::valid() const{
    return m_mngr.valid();
}

const Dstring& Lexer::str() const{
    return m_mngr.str();
}

Locator Lexer::locator() const{
    return Locator(m_mngr.str(), m_mngr.index());
}

DBC_END