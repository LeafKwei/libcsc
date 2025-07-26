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
        Dchar ch = picker.pick();
        if(!canRead(ch)){
            picker.backward();
            break;
        }

        token.buffer.push_back(ch);
    }

    return token;
 }

inline bool EmptyReader::canRead(Dchar ch) const noexcept{
    return isBlank(ch);
}

 inline bool BlankReader::isThisReader(CharPicker &picker) const noexcept{
    return canRead(picker.tryPick());
 }

 //=================== BlankReader ===================
 

/*
void StringReader::readToken(const Dstring &raw, Dstring &buffer, Locator &locator) const noexcept{
    bool isEscaped = false;

    for(int i = locator.index; i < raw.length(); i++){
        Dchar ch = raw.at(i);

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

Dchar StringReader::escape(Dchar ch) const noexcept{
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

*/
