#include "dbc/lex/readers.hpp"
DBC_BEGIN

//=================== EmptyReader ===================
TokenType EmptyReader::type() const noexcept{
    return TokenType::Empty;
}

bool EmptyReader::canRead(DbcChar ch) const noexcept{
    return false;
}

bool EmptyReader::isThisType(DbcChar ch) const noexcept{
    return canRead(ch);
}

void EmptyReader::readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept{
    return;
}

//=================== UnknownReader ===================
TokenType UnknownReader::type() const noexcept{
    return TokenType::Empty;
}

bool UnknownReader::canRead(DbcChar ch) const noexcept{
    return false;
}

bool UnknownReader::isThisType(DbcChar ch) const noexcept{
    return canRead(ch);
}

void UnknownReader::readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept{
    return;
}

//=================== BlankReader ===================
TokenType BlankReader::type() const noexcept{
    return TokenType::Blank;
}

bool BlankReader::canRead(DbcChar ch) const noexcept{
    return ch <=32 ? true : false;
}

bool BlankReader::isThisType(DbcChar ch) const noexcept{
    return canRead(ch);
}

void BlankReader::readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept{
    for(int i = locator.index; i < raw.length(); i++){
        DbcChar ch = raw.at(i);

        if(!canRead(ch)){
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

bool StringReader::canRead(DbcChar ch) const noexcept{
     if(!(BlankReader().isThisType(ch)) && !(OperatorReader().isThisType(ch))){
        return true;
    }

    return false;
}

bool StringReader::isThisType(DbcChar ch) const noexcept{
    return canRead(ch);
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

        if(isEscaped){
            isEscaped = false;
            buffer.push_back(escape(ch));
            updateLocator(ch, locator);
            continue;
        }

        if(canRead(ch)){
            buffer.push_back(ch);
            updateLocator(ch, locator);
            continue;
        }

        break;
    }
}

DbcChar StringReader::escape(DbcChar ch) const noexcept{
    switch(ch){
        case '0':
            return '\0';
        case 't':
            return '\t';
        case 'n':
            return '\n';
        case 'r':
            return '\r';
        case 'b':
            return '\b';
        default:
            return ch;
    }
}

//=================== OperatorReader ===================
TokenType OperatorReader::type() const noexcept{
    return TokenType::Operator;
}

bool OperatorReader::canRead(DbcChar ch) const noexcept{
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

bool OperatorReader::isThisType(DbcChar ch) const noexcept{
    return canRead(ch);
}

void OperatorReader::readToken(const DbcString &raw, DbcString &buffer, Locator &locator) const noexcept{
    for(int i = locator.index; i < raw.length(); i++){
        DbcChar ch = raw.at(i);

        if(!canRead(ch)){
            break;
        }

        buffer.push_back(ch);
        updateLocator(ch, locator);
    }
}

DBC_END