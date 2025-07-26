#include <iostream>
#include "dbc/lex/readers.hpp"
#include "dbc/lex/LexHelper.hpp"
DBC_BEGIN

LexHelper::LexHelper(){
    installReaders();
    resetLocator();
}

LexHelper::~LexHelper(){

}

bool LexHelper::hasMore(const Dstring &raw) const noexcept{
    return m_locator.index < raw.length();
}

Token LexHelper::readToken(const Dstring &raw) {
    Token token;
    token.type = TokenType::Unknown;



    return token;
}

Token LexHelper::readToken(const Dstring &raw, TokenType type){
    Token token;
    token.type = TokenType::Unknown;

    

    return token;
}

int LexHelper::numberOfRow() const noexcept{
    return m_locator.row;
}

int LexHelper::numberOfCol() const noexcept{
    return m_locator.col;
}

const Locator& LexHelper::locator() const noexcept{
    return m_locator;
}

void LexHelper::setLocator(const Locator &locator) noexcept{
    m_locator = locator;
}

void LexHelper::resetLocator() noexcept{
    m_locator.index = 0;
    m_locator.row = 0;
    m_locator.col = 0;
}

void LexHelper::installReaders(){
    
}

DBC_END