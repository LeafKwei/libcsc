#include <iostream>
#include "dbc/lex/functions.hpp"
#include "dbc/lex/LexHelper.hpp"

DBC_BEGIN

using std::string;

//====================== LexHelper ===============
LexHelper::LexHelper():
    m_index(0),  
    m_rowCounter(0), 
    m_colCounter(0)
{
    // For m_tokenTypeBranches.
    m_tokenTypeBranches.push_back(TokenTypeBranch(':', TokenType::Operator));
    m_tokenTypeBranches.push_back(TokenTypeBranch('=', TokenType::Operator));
    m_tokenTypeBranches.push_back(TokenTypeBranch('\'', TokenType::Operator));
    m_tokenTypeBranches.push_back(TokenTypeBranch('\"', TokenType::Operator));
    m_tokenTypeBranches.push_back(TokenTypeBranch(';', TokenType::Operator));
    m_tokenTypeBranches.push_back(TokenTypeBranch(' ', TokenType::Blank));
    m_tokenTypeBranches.push_back(TokenTypeBranch('\t', TokenType::Blank));
    m_tokenTypeBranches.push_back(TokenTypeBranch('\n', TokenType::Blank));

    //For m_optionBranches.
    
}

LexHelper::~LexHelper(){}


DbcString LexHelper::readToken(const DbcString &raw){
    return readToken(raw, decide);
}

DbcString LexHelper::readToken(const DbcString &raw, std::function<Option(DbcChar, TokenType, TokenType, const DbcString&)> decider){
    if(m_index >= raw.length()) return string("");

    string buffer("");
    int index = m_index;
    UpdatePack pack;
    Option option = Option::Pick;
    TokenType charType = TokenType::Empty;
    TokenType lastCharType = TokenType::Empty;

    while(option != Option::Finish){
        DbcChar ch = raw.at(index);
        charType = tokenTypeOf(ch);
        option = decider(ch, charType, lastCharType, buffer);
        
        store(pack);
        switchToHandler(option, ch, buffer, pack, charType, lastCharType);
        update(pack);
        lastCharType = pack.type;
    }

    return buffer;
}

TokenType LexHelper::tokenTypeOf(DbcChar ch){
    for(auto &branch : m_tokenTypeBranches){
        if(ch == branch.ch){
            return branch.type;
        }
    }

    std::cout << "[libdbc] No token-type-branch match `" << ch << "`" << std::endl;
    return TokenType::Other;
}

void LexHelper::switchToHandler(Option option, DbcChar ch, DbcString &buffer, UpdatePack &pack, TokenType charType, TokenType lastCharType){
    for(auto &branch : m_optionBranches){
        if(branch.option == option){
            branch.handler(ch, buffer, pack, charType, lastCharType);
        }
    }

    std::cout << "[libdbc] No option-branch match option `" << static_cast<int>(option) << "`" << std::endl;
}

void LexHelper::store(UpdatePack &pack) noexcept{
    pack.index = this -> m_index;
    pack.row = this -> m_rowCounter;
    pack.col = this -> m_colCounter;
}

void LexHelper::update(const UpdatePack &pack) noexcept{
    this -> m_index = pack.index;
    this -> m_rowCounter = pack.row;
    this -> m_colCounter = pack.col;
}

DBC_END