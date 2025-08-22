#include "csc/lex/Lexer.hpp"
#include "csc/lex/readers.hpp"
CSC_BEGIN

Lexer::Lexer() : Lexer(""){ }
Lexer::Lexer(const CscStr &str) : m_mngr(str){ }

Token Lexer::nextToken(){
    return nextTokenFrom(m_mngr);
}

bool Lexer::valid() const{
    return m_mngr.valid();
}

const CscStr& Lexer::str() const{
    return m_mngr.str();
}

Locator Lexer::locator() const{
    return Locator(m_mngr.str(), m_mngr.index());
}

CSC_END