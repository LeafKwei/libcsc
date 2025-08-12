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

bool DescriptionReader::canRead(Dchar ch){
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

bool IdentifierReader::canRead(Dchar ch){
    return isIdentifier(ch);
}

//============== OperatorReader =============
bool OperatorReader::isThisType(CharMngr &mngr){
    return mngr.valid() && isOperator(mngr.getch());
}

TokenType OperatorReader::type(){
    return TokenType::Operator;
}

bool OperatorReader::canRead(Dchar ch){
    return isOperator(ch);
}

//============== NumberReader =============
Token NumberReader::read(CharMngr &mngr){
    Token token{TokenType::Aborted};
    if(!isThisType(mngr)) return token;

    if(m_type == 2) readHex(token, mngr);
    if(m_type == 0) readNumber(token, mngr);
    return token;
}

bool NumberReader::isThisType(CharMngr &mngr){
    if(isHex(mngr)){
        m_type = 2;
        return true;
    }

    if(mngr.valid() && isNumber(mngr.getch())){
        m_type = 0;
        return true;
    }

    return false;
}

TokenType NumberReader::type(){
    return TokenType::Number;
}

bool NumberReader::canRead(Dchar ch){
    return false;
}

bool NumberReader::isHex(CharMngr &mngr){
    auto idx = mngr.index();

    if((mngr.valid() && mngr.forward() == '0') && (mngr.valid() && mngr.forward() == 'x')){
        mngr.seek(CharMngr::Set, idx);
        return true;
    }

    mngr.seek(CharMngr::Set, idx);
    return false;
}

void NumberReader::readNumber(Token &token, CharMngr &mngr){
    token.type = TokenType::Number;

read:
    while(mngr.valid()){
        if(!isNumber(mngr.getch())) break;
        token.buffer.push_back(mngr.forward());
    }

    //Read it as float If there is a dot.
    if(mngr.valid() && isDot(mngr.getch()) && m_type == 0){
        token.buffer.push_back(mngr.forward());  //Push dot.
        m_type = 1;
        goto read;
    }

    //If this number is not ending with blank.
    if(mngr.valid() && !isBlank(mngr.getch())){
        token.type = TokenType::Unexcepted;
    }
}

void NumberReader::readHex(Token &token, CharMngr &mngr){
    token.type = TokenType::Number;

    //Put 0x
    token.buffer.push_back(mngr.forward());
    token.buffer.push_back(mngr.forward());

    //Put other
    while(mngr.valid()){
        if(!isHexNumber(mngr.getch())) break;
        token.buffer.push_back(mngr.forward());
    }

    if(mngr.valid() && !isBlank(mngr.getch())){
        token.type = TokenType::Unexcepted;
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
    if(mngr.valid() && mngr.getch() == '"'){
        return true;
    }

    return false;
}

TokenType StringReader::type(){
    return TokenType::String;
}

bool StringReader::canRead(Dchar ch){
    return false;
}

void StringReader::readString(Token &token, CharMngr &mngr){
    mngr.forward();  //skip first quota
    token.type = TokenType::String;

    bool escape = false;
    while(mngr.valid()){
        Dchar ch = mngr.forward();

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
            break;
        }

        token.buffer.push_back(ch);
    }

    //If there is no quota as ending
    if(!(mngr.valid())){
        token.type = TokenType::Unexcepted;
        return;
    }

    //Skip ending quota
    mngr.forward();
}


DBC_END