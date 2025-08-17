#include "dbc/lex/PureLexer.hpp"
#include "dbc/lex/readers.hpp"
DBC_BEGIN

PureLexer::PureLexer() : m_autoSkipBlank(true){
    installReaders();
}

Token PureLexer::nextTokenFrom(CharMngr &mngr){
    Token token;
    auto idx = 0;

    while(mngr.valid() && idx < m_readers.size()){
        auto &reader = m_readers.at(idx);
        token = reader -> read(mngr);
        
        if(token.type == TokenType::Aborted){
            ++idx;
            continue;
        }

        if(isIgnoredToken(token.type)){
            idx = 0;
            continue;
        }

        return tokenConvert(token);
    }

    token.type = mngr.valid() ? TokenType::Unexcepted : TokenType::Aborted;
    return token;
}

void PureLexer::setAutoSkipBlank(bool b){
    m_autoSkipBlank = b;
}

Token& PureLexer::tokenConvert(Token &token){
    switch(token.type){
        case TokenType::Identifier:
            if(token.buffer == "true" || token.buffer == "false"){
                token.type = TokenType::Keyword;
            }
            break;
    }

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


DBC_END