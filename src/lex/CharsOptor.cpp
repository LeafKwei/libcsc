#include "dbc/lex/CharsOptor.hpp"
DBC_BEGIN

CharsOptor::CharsOptor(const Dstring &raw) : m_raw(raw), m_index(0){}
CharsOptor::CharsOptor(const Dstring &raw, int index) : m_raw(raw), m_index(index){}
CharsOptor::CharsOptor(const CharsOptor &oth) : m_raw(oth.m_raw), m_index(oth.m_index){}

bool CharsOptor::startWith(const Dstring &prefix) const noexcept{
    if(m_index < 0) return false;
    int len = prefix.size();
    if(m_index + len > m_raw.size()) return false;

    return m_raw.substr(m_index, len) == prefix;
}

DBC_END