#include "dbc/lex/readers.hpp"
#include "dbc/lex/functions.hpp"
DBC_BEGIN

//============== CommonReader =============
Token CommonReader::read(CharMngr &mngr){
    Token token{TokenType::Aborted};
    if(!isThisType(mngr)) return token;

    while(mngr.valid()){
        if(!canRead(mngr.getch())) break;
        token.buffer.push_back(mngr.forward());
    }

    token.type = type();
    return token;
}

bool CommonReader::isThisType(CharMngr &mngr){
    return false;
}

TokenType CommonReader::type(){
    return TokenType::Aborted;
}

bool CommonReader::canRead(Dchar ch){
    return false;
}

//============== BlankReader =============
bool BlankReader::isThisType(CharMngr &mngr){
    return mngr.valid() && isBlank(mngr.getch());
}

TokenType BlankReader::type(){
    return TokenType::Blank;
}

bool BlankReader::canRead(Dchar ch){
    return isBlank(ch);
}

//============== IdentifierReader =============
bool IdentifierReader::isThisType(CharMngr &mngr){
    return mngr.valid() && (isAlpha(mngr.getch()) || mngr.getch() == '_');
}

TokenType IdentifierReader::type(){
    return TokenType::Identifier;
}

bool IdentifierReader::canRead(Dchar ch){
    return isIdentifier(ch);
}

//============== OperatorReader =============
bool IdentifierReader::isThisType(CharMngr &mngr){
    return mngr.valid() && isOperator(mngr.getch());
}

TokenType IdentifierReader::type(){
    return TokenType::Operator;
}

bool IdentifierReader::canRead(Dchar ch){
    return isOperator(ch);
}

//============== NumberReader =============
Token NumberReader::read(CharMngr &mngr){
    Token token{TokenType::Aborted};
    if(!isThisType(mngr)) return token;

    auto cnt = m_directly;

    //For prefix(e.g 0x)
    while(mngr.valid() && cnt){
        token.buffer.push_back(mngr.forward());
        --cnt;
    }
}

bool NumberReader::isThisType(CharMngr &mngr){
    
}

TokenType NumberReader::type(){
    
}

bool NumberReader::canRead(Dchar ch){
    
}

bool NumberReader::isGeneralNumber(CharMngr &mngr) {
    
}

bool NumberReader::isHexNumber(CharMngr &mngr){
    
}

DBC_END