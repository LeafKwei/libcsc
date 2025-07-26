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
    m_readers.push_back(std::make_shared<BlankReader>());
    m_readers.push_back(std::make_shared<GeneralReader>());
    m_readers.push_back(std::make_shared<OperatorReader>());
    m_readers.push_back(std::make_shared<DelimitorReader>());
}

void LexHelper::installExplicitReaders(){
    m_explicitReaders.push_back(std::make_shared<BlankReader>());
    m_explicitReaders.push_back(std::make_shared<GeneralReader>());
    m_explicitReaders.push_back(std::make_shared<OperatorReader>());
    m_explicitReaders.push_back(std::make_shared<DelimitorReader>());
    m_explicitReaders.push_back(std::make_shared<EmptyReader>());
    m_explicitReaders.push_back(std::make_shared<UnknownReader>());
}

DBC_END