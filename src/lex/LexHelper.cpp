#include <iostream>
#include "dbc/lex/readers.hpp"
#include "dbc/lex/LexHelper.hpp"
DBC_BEGIN

LexHelper::LexHelper(const Dstring &raw) : m_charMngr(raw){
    installReaders();
}

LexHelper::~LexHelper(){

}

void LexHelper::installReaders(){
    m_readers.push_back(std::make_shared<TokenReader>(new BlankReader()));
    m_readers.push_back(std::make_shared<TokenReader>(new GeneralReader()));
    m_readers.push_back(std::make_shared<TokenReader>(new OperatorReader()));
    m_readers.push_back(std::make_shared<TokenReader>(new DelimitorReader()));
}

void LexHelper::installExplicitReaders(){
    m_readers.push_back(std::make_shared<TokenReader>(new EmptyReader()));
    m_readers.push_back(std::make_shared<TokenReader>(new UnknownReader()));
    
}

DBC_END