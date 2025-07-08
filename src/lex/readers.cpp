#include "dbc/lex/readers.hpp"
DBC_BEGIN

//=================== BlankReader ===================
TokenType BlankReader::type() const noexcept{
    return TokenType::Blank;
}

bool BlankReader::isThisType(DbcChar ch) const noexcept{
    return ch <=32 ? true : false;
}

void BlankReader::readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept{
    for(int i = locator.index; i < raw.length(); i++){
        DbcChar ch = raw.at(i);

        if(!isThisType(ch)){
            break;
        }

        buffer.push_back(ch);
        updateLocator(ch, locator);
    }
}

//=================== StringReader ===================
TokenType StringReader::type() const noexcept{
    return TokenType::String;
}

bool StringReader::isThisType(DbcChar ch) const noexcept{
    if(!(BlankReader().isThisType(ch)) && !(OperatorReader().isThisType(ch))){
        return true;
    }

    return false;
}

void StringReader::readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept{
    bool isEscaped = false;

    for(int i = locator.index; i < raw.length(); i++){
        DbcChar ch = raw.at(i);

        if(ch == '\\'){
            isEscaped = true;
            updateLocator(ch, locator);
            continue;
        }

        if(isEscaped || isThisType(ch)){
            isEscaped = false;
            buffer.push_back(ch);
            updateLocator(ch, locator);
            continue;
        }

        break;
    }
}

//=================== OperatorReader ===================
TokenType OperatorReader::type() const noexcept{
    return TokenType::Operator;
}

bool OperatorReader::isThisType(DbcChar ch) const noexcept{
    switch(ch){
        case '\"':
        case '=':
        case ':':
        case ';':
            return true;
        default:
            return false;
    }
}

void OperatorReader::readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept{
    for(int i = locator.index; i < raw.length(); i++){
        DbcChar ch = raw.at(i);

        if(!isThisType(ch)){
            break;
        }

        buffer.push_back(ch);
        updateLocator(ch, locator);
    }
}

DBC_END