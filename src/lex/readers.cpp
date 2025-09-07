#include <iostream>
#include <sstream>
#include "csc/lex/PureLexer.hpp"
#include "csc/lex/readers.hpp"
#include "csc/lex/functions.hpp"
CSC_BEGIN

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

bool CommonReader::canRead(CscChar ch){
    return false;
}

//============== BlankReader =============
bool BlankReader::isThisType(CharMngr &mngr){
    return mngr.valid() && isBlank(mngr.getch());
}

TokenType BlankReader::type(){
    return TokenType::Blank;
}

bool BlankReader::canRead(CscChar ch){
    return isBlank(ch);
}

//============== DescriptionReader =============
Token DescriptionReader::read(CharMngr &mngr){
    if(!isThisType(mngr)) return {TokenType::Aborted};

    while(mngr.valid()){
        if(!canRead(mngr.getch())) break;
        mngr.forward();
    }

    return {TokenType::Ignored};
}

bool DescriptionReader::isThisType(CharMngr &mngr){
    return mngr.valid() && (mngr.getch() == ';');
}

TokenType DescriptionReader::type(){
    return TokenType::Ignored;
}

bool DescriptionReader::canRead(CscChar ch){
    if(!isNewLine(ch)) return true;
    return false;
}

//============== IdentifierReader =============
bool IdentifierReader::isThisType(CharMngr &mngr){
    return mngr.valid() && (isAlpha(mngr.getch()) || mngr.getch() == '_');
}

TokenType IdentifierReader::type(){
    return TokenType::Identifier;
}

bool IdentifierReader::canRead(CscChar ch){
    return isIdentifier(ch);
}

//============== OperatorReader =============
bool OperatorReader::isThisType(CharMngr &mngr){
    return mngr.valid() && isOperator(mngr.getch());
}

TokenType OperatorReader::type(){
    return TokenType::Operator;
}

bool OperatorReader::canRead(CscChar ch){
    return isOperator(ch);
}

//============== NumberReader =============
Token NumberReader::read(CharMngr &mngr){
    Token token{TokenType::Aborted};
    if(!isThisType(mngr)) return token;

    readPrefix(token, mngr);

    m_num = 0;
    token.type = TokenType::Number;
    if(m_type == 1) readHex(token, mngr);
    if(m_type == 0) readNumber(token, mngr);

    //If no valid number character was read.
    if(m_num == 0){
        token.type = TokenType::Unexcepted;
    }

    //If this number is not ending with blank or separator.
    if(mngr.valid() && (!isBlank(mngr.getch()) && !(isSeparator(mngr.getch())))){
       token.type = TokenType::Unexcepted;
    }

    return token;
}

bool NumberReader::isThisType(CharMngr &mngr){
    if(mngr.valid() && isNumber(mngr.getch())) return true;
    
    /* Check if this token has +- as prefix. */
    if(mngr.valid() && (mngr.getch() == '+' || mngr.getch() == '-')) return true;

    /* Check if this token has 0x as prefix. */
    if(mngr.index() + 1 >= mngr.length()) return false;
    if(mngr.at(mngr.index()) == '0' && mngr.at(mngr.index() + 1) == 'x') return true;

    return false;
}

TokenType NumberReader::type(){
    return TokenType::Number;
}

bool NumberReader::canRead(CscChar ch){
    return false;
}

void NumberReader::readPrefix(Token &token, CharMngr &mngr){
    /* Checking for hex is must be first, because the prefix '0x' contain number 0. */
    if(mngr.at(mngr.index()) == '0' && mngr.at(mngr.index() + 1) == 'x'){
        m_type = 1;
        token.buffer.push_back(mngr.forward());
        token.buffer.push_back(mngr.forward());
        return;
    }

    if(mngr.valid() && isNumber(mngr.getch())){
        m_type = 0;
        return;
    }
    
    if(mngr.valid() && (mngr.getch() == '+' || mngr.getch() == '-')){
        m_type = 0;
        token.buffer.push_back(mngr.forward());
        return;
    }
}

void NumberReader::readHex(Token &token, CharMngr &mngr){
    while(mngr.valid()){
        if(!isHexNumber(mngr.getch())) break;
        token.buffer.push_back(mngr.forward());
        m_num++;
    }
}

void NumberReader::readNumber(Token &token, CharMngr &mngr){
    bool dot = true;

    while(mngr.valid()){
        auto ch = mngr.getch();
        if(!isNumber(ch) && !(dot && ch == '.')) break;  //If ch neither number nor first dot.
        if(ch == '.') dot = false;
        token.buffer.push_back(mngr.forward());
        m_num++;
    }
}

//============== StringReader =============
Token StringReader::read(CharMngr &mngr){
    Token token{TokenType::Aborted};
    if(!isThisType(mngr)) return token;
    readString(token, mngr);
    return token;
}

bool StringReader::isThisType(CharMngr &mngr){
    return mngr.valid() && mngr.getch() == '"';
}

TokenType StringReader::type(){
    return TokenType::String;
}

bool StringReader::canRead(CscChar ch){
    return false;
}

void StringReader::readString(Token &token, CharMngr &mngr){
    mngr.forward();  //skip first quota
    token.type = TokenType::String;

    bool escape = false;
    while(mngr.valid()){
        CscChar ch = mngr.forward();

        if(escape){
            escape = false;
            token.buffer.push_back(escapeTo(ch));
            continue;
        }

        if(isEscape(ch)){
            escape = true;
            continue;
        }

        if(ch == '"'){
            return;
        }

        token.buffer.push_back(ch);
    }

    if(!(mngr.valid())){ //If there is no ending quota
        token.type = TokenType::Unexcepted;
    }
}

//============== ArrayReader =============
Token ArrayReader::read(CharMngr &mngr){
    Token token{TokenType::Aborted};
    if(!isThisType(mngr)) return token;

    token.type = TokenType::Array;
    auto idx = mngr.index();
    mngr.forward();   //Skip first '{'

    /* Read all characters in '{}'*/
    while(mngr.valid()){
        if(mngr.getch() == '}') break;
        token.buffer.push_back(mngr.forward());
    }

    if(!mngr.valid()){        //Restore index if token is unexcepted
        mngr.seek(CharMngr::Set, idx);
        token.type = TokenType::Unexcepted;
        return token;
    }

    mngr.forward(); //Skip ending '}'

    return token;
}

bool ArrayReader::isThisType(CharMngr &mngr){
    return mngr.valid() && mngr.getch() == '{';
}

TokenType ArrayReader::type(){
    return TokenType::Array;
}

bool ArrayReader::canRead(CscChar ch){
    return false;
}

CSC_END