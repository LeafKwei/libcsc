#include "csc/lex/PureLexer.hpp"
#include "csc/lex/readers.hpp"
CSC_BEGIN

PureLexer::PureLexer() : m_autoSkipBlank(true){
    installReaders();
    installConverters();
}

Token PureLexer::nextTokenFrom(CharMngr &mngr){
    Token token;
    Size_t idx = 0;

    while(mngr.valid() && idx < m_readers.size()){
        auto &reader = m_readers.at(idx);
        if(!(reader -> readable(mngr))){
            ++idx; 
            continue;
        }

        token = reader -> read(mngr);

        if(isIgnoredToken(token.type)){
            idx = 0;
            continue;
        }

        return identifierConverter(token);
    }

    token.type = mngr.valid() ? TokenType::Unexcepted : TokenType::Aborted;
    return token;
}

void PureLexer::setAutoSkipBlank(bool b){
    m_autoSkipBlank = b;
}

Token& PureLexer::identifierConverter(Token &token){
    if(token.type != TokenType::Identifier) return token;
    auto pos = m_converters.find(token.buffer);
    if(pos == m_converters.end()) return token;
    
    token.type = pos -> second;
    return token;
}

void PureLexer::installReaders(){
    m_readers.push_back(std::make_shared<BlankReader>());
    m_readers.push_back(std::make_shared<IdentifierReader>());
    m_readers.push_back(std::make_shared<OperatorReader>());
    m_readers.push_back(std::make_shared<NumberReader>());
    m_readers.push_back(std::make_shared<DescriptionReader>());
    m_readers.push_back(std::make_shared<StringReader>());
    m_readers.push_back(std::make_shared<ArrayReader>());
}

void PureLexer::installConverters(){
    m_converters.insert({"true", TokenType::Keyword});
    m_converters.insert({"false", TokenType::Keyword});
}

CSC_END