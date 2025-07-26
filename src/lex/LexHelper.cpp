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
    
}

DBC_END