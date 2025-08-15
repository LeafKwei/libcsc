#include "dbc/lex/Lexer.hpp"
#include "dbc/lex/readers.hpp"
DBC_BEGIN

Lexer::Lexer(const Dstring &str) : 
    m_autoSkipBlank(true), m_mngr(str)
{
    installReaders();
    installConverters();
}

Token Lexer::nextToken(){
    Token token;
    auto idx = 0;

    while(valid() && idx < m_readers.size()){
        auto &reader = m_readers.at(idx);
        token = reader -> read(m_mngr);
        
        if(token.type == TokenType::Aborted){
            ++idx;
            continue;
        }

        if(isIgnoredToken(token.type)){
            idx = 0;
            continue;
        }

        return identifierConverter(token);
    }

    token.type = valid() ? TokenType::Unexcepted : TokenType::Aborted;
    return token;
}

bool Lexer::valid() const{
    return m_mngr.valid();
}

const Dstring& Lexer::str() const{
    return m_mngr.str();
}

void Lexer::setAutoSkipBlank(bool b){
    m_autoSkipBlank = b;
}

Locator Lexer::locator() const{
    return Locator(m_mngr.str(), m_mngr.index());
}

Token& Lexer::identifierConverter(Token &token){
    if(token.type != TokenType::Identifier) return token;
    auto pos = m_converters.find(token.buffer);
    if(pos == m_converters.end()) return token;
    
    token.type = pos -> second;
    return token;
}

void Lexer::installReaders(){
    m_readers.push_back(std::make_shared<BlankReader>());
    m_readers.push_back(std::make_shared<IdentifierReader>());
    m_readers.push_back(std::make_shared<OperatorReader>());
    m_readers.push_back(std::make_shared<NumberReader>());
    m_readers.push_back(std::make_shared<DescriptionReader>());
    m_readers.push_back(std::make_shared<StringReader>());
    m_readers.push_back(std::make_shared<ArrayReader>());
}

void Lexer::installConverters(){
    m_converters.insert({"true", TokenType::Keyword});
    m_converters.insert({"false", TokenType::Keyword});
}

DBC_END