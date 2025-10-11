#include "csc/lex/Lexer.hpp"
#include "csc/lex/readers.hpp"
CSC_BEGIN

Lexer::Lexer(crString str) : m_mngr(str){
    
}

LexResult Lexer::nextResult(){
    return m_pure.nextResultFrom(m_mngr);
}

bool Lexer::valid() const{
    return m_mngr.valid();
}

crString Lexer::str() const{
    return m_mngr.str();
}

Locator Lexer::locator(int offset) const{
    return Locator(m_mngr.str(), m_mngr.index() + offset);
}

CSC_END