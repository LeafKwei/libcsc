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
    int index = locator.index;

    for(int i = index; i < raw.length(); i++){
        DbcChar ch = raw.at(i);

        if(!isThisType(ch)){
            break;
        }

        buffer.push_back(ch);
        updateLocator(ch, locator);
    }
}

inline void BlankReader::updateLocator(DbcChar ch, Locator &locator) const noexcept{
    locator.index++;
    locator.col++;

    if(ch == '\n'){
        locator.row++;
        locator.col = 0;
    }
}

//=================== StringReader ===================


//=================== OperatorReader ===================


DBC_END