#include <iostream>
#include "dbc/lex/readers.hpp"
#include "dbc/lex/LexHelper.hpp"
DBC_BEGIN

LexHelper::LexHelper(){
    installReaders();
    resetLocation();
}

LexHelper::~LexHelper(){

}

bool LexHelper::hasMore(const DbcString &raw) const noexcept{
    return m_locator.index < raw.length();
}

Token LexHelper::readToken(const DbcString &raw) {
    Token token;
    token.type = TokenType::Unknown;

    if(m_locator.index < raw.length()){
        for(auto &reader : m_readerBranches){
            if(reader -> isThisType(raw.at(m_locator.index))){
                reader -> readToken(raw, token.buffer, m_locator);
                token.type = reader -> type();
                break;
            }
        }
    }

    return token;
}

Token LexHelper::readToken(const DbcString &raw, TokenType type){
    Token token;
    token.type = TokenType::Unknown;

    if(m_locator.index < raw.length()){
        for(auto &reader : m_readerBranches){
            if(reader -> type() == type){
                reader -> readToken(raw, token.buffer, m_locator);
                token.type = reader -> type();
                break;
            }
        }
    }

    return token;
}

Token LexHelper::readToken(const DbcString &raw, const TokenReader &reader){
    Token token;
    token.type = TokenType::Unknown;

    if(m_locator.index < raw.length()){
        reader.readToken(raw, token.buffer, m_locator);
        token.type = reader.type();
    }
    
    return token;
}

int LexHelper::numberOfRow() const noexcept{
    return m_locator.row;
}

int LexHelper::numberOfCol() const noexcept{
    return m_locator.col;
}

int LexHelper::numberOfLocation() const noexcept{
    return m_locatorStack.size();
}

void LexHelper::pushLocation() noexcept{
    m_locatorStack.push(m_locator);
}

void LexHelper::popLocation() noexcept{
    m_locator =  m_locatorStack.top();
    m_locatorStack.pop();
}

void LexHelper::resetLocation() noexcept{
    m_locator.index = 0;
    m_locator.row = 0;
    m_locator.col = 0;
}

void LexHelper::installReaders(){
    m_readerBranches.push_back(std::make_shared<BlankReader>());
    m_readerBranches.push_back(std::make_shared<StringReader>());
    m_readerBranches.push_back(std::make_shared<OperatorReader>());

    //Keep these two at end
    m_readerBranches.push_back(std::make_shared<EmptyReader>());
    m_readerBranches.push_back(std::make_shared<UnknownReader>());
}

DBC_END