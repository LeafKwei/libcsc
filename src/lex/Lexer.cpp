#include "dbc/lex/Lexer.hpp"
#include "dbc/lex/readers.hpp"
#include "dbc/lex/ctrls.hpp"
DBC_BEGIN

Lexer::Lexer(const Dstring &str) : 
    m_autoSkipBlank(true), m_mngr(str)
{
    installReaders();
    installCtrls();
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

        return keywordFilter(token);
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

Token& Lexer::keywordFilter(Token &token){
    if(token.type != TokenType::Identifier) return token;
    auto pos = m_ctrls.find(token.buffer);
    if(pos == m_ctrls.end()) return token;

    auto &ctrl = pos -> second;
    token.type = TokenType::Keyword;
    ctrl -> changeReaderRule(m_readers);
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

void Lexer::installCtrls(){
    m_ctrls.insert({"true", std::make_shared<TrueCtrl>()});
    m_ctrls.insert({"false", std::make_shared<FalseCtrl>()});
}

DBC_END