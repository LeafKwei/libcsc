#include "csc/lex/Lexer.hpp"
CSC_BEGIN

Lexer::Lexer(const String &str) : mngr_(str){
    
}

LxErrno Lexer::readToken(CharMngr &mngr, TokenPool &pool){
    return pure_.readToken(mngr, pool);
}

CSC_END