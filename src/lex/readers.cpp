#include "dbc/lex/readers.hpp"
#include "dbc/lex/functions.hpp"
DBC_BEGIN

//=================== EmptyReader ===================

Token EmptyReader::readToken(CharPicker &picker) const noexcept{
    return {TokenType::Empty};
}

inline bool EmptyReader::canRead(Dchar ch) const noexcept{
    return false;
}

inline bool EmptyReader::isThisReader(CharPicker &picker) const noexcept{
    return false;
}

//=================== UnknownReader ===================
Token UnknownReader::readToken(CharPicker &picker) const noexcept{
   return {TokenType::Unknown};
}

//=================== BlankReader ===================
Token BlankReader::readToken(CharPicker &picker) const noexcept{
    if(!isThisReader(picker)) return {TokenType::Unknown};

    Token token{TokenType::Blank};
    while(picker.hasMore()){
        if(!canRead(picker.tryPick())){
            break;
        }

        token.buffer.push_back(picker.pick());
    }

    return token;
}

inline bool EmptyReader::canRead(Dchar ch) const noexcept{
    return isBlank(ch);
}

inline bool BlankReader::isThisReader(CharPicker &picker) const noexcept{
    return canRead(picker.tryPick());
}

//=================== IdentifierReader ===================
Token IdentifierReader::readToken(CharPicker &picker) const noexcept{
    if(!isThisReader(picker)) return {TokenType::Unknown};

    bool escape = false;
    Token token{TokenType::Identifier};

    while(picker.hasMore()){
        if(!canRead(picker.tryPick())){
            break;
        }

        token.buffer.push_back(picker.pick());
    }

    return token;
}

inline bool IdentifierReader::canRead(Dchar ch) const noexcept{
    return isIdentifier(ch) || isNumber(ch);
}

inline bool IdentifierReader::isThisReader(CharPicker &picker) const noexcept{
    return isIdentifier(picker.tryPick());
}

//=================== NumberReader ===================
Token NumberReader::readToken(CharPicker &picker) const noexcept{
    if(!isThisReader(picker)) return {TokenType::Unknown};

    
}

inline bool NumberReader::canRead(Dchar ch) const noexcept{

}

inline bool NumberReader::isThisReader(CharPicker &picker) const noexcept{
    
}

//=================== StringReader ===================
/*
    bool escape = false;
    Token token{TokenType::Identifier};

    while(picker.hasMore()){
        if(!isEscape(picker.tryPick()) && (!escape)){
            picker.forward();
            escape = true;
            continue;
        }

        if(escape){
            escape = false;
            token.buffer.push_back(doEscape(picker.pick()));
            continue;
        }

        if(!canRead(picker.tryPick())){
            break;
        }
*/

//=================== LongStringReader ===================



//=================== OperatorReader ===================
Token OperatorReader::readToken(CharPicker &picker) const noexcept{
    if(!isThisReader(picker)) return {TokenType::Unknown};

    Token token{TokenType::Operator};
    while(picker.hasMore()){
        if(!canRead(picker.tryPick())){
            break;
        }

        token.buffer.push_back(picker.pick());
    }

    return token;
}

inline bool OperatorReader::canRead(Dchar ch) const noexcept{
    return isOperator(ch);
}

inline bool OperatorReader::isThisReader(CharPicker &picker) const noexcept{
    return canRead(picker.tryPick());
}

//=================== DelimitorReader ===================
Token DelimitorReader::readToken(CharPicker &picker) const noexcept{
    if(!isThisReader(picker)) return {TokenType::Unknown};

    Token token{TokenType::Operator};
    while(picker.hasMore()){
        if(!canRead(picker.tryPick())){
            break;
        }

        token.buffer.push_back(picker.pick());
    }

    return token;
}

inline bool DelimitorReader::canRead(Dchar ch) const noexcept{
    return isDelimitor(ch);
}

inline bool DelimitorReader::isThisReader(CharPicker &picker) const noexcept{
    return canRead(picker.tryPick());
}

