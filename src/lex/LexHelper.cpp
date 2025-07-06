#include "dbc/lex/LexHelper.hpp"

DBC_BEGIN

LexHelper::LexHelper() : m_nextIndex(0),  m_rowCounter(0), m_colCounter(0), m_lastCharType(CharType::Empty){}
LexHelper::~LexHelper(){}



DBC_END