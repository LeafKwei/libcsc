#include "csc/lex/Lexer.hpp"
CSC_BEGIN

Lexer::Lexer(const String &str) : mngr_(str){
    
}

Index_t Lexer::index() const noexcept{
    return mngr_.index();
}

LxErrno Lexer::readToken(TokenPool &pool){
    return pure_.readToken(mngr_, pool);
}

CSC_END