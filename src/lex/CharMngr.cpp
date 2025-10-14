#include "csc/lex/CharMngr.hpp"
CSC_BEGIN

CharMngr::CharMngr(crString str, int index) : m_str(str), m_index(index){
    if(m_index < 0) m_index = 0;
    else if(m_index > m_str.size()) m_index = m_str.size();
}

int CharMngr::index() const{
    return m_index;
}

int CharMngr::length() const{
    return m_str.size();
}

bool CharMngr::valid() const{
    return (m_index >= 0) && (m_index < m_str.size());
}

Char CharMngr::at(int index) const{
    return m_str.at(index);
}

Char CharMngr::getch() const{
    return m_str.at(m_index);
}

Char CharMngr::forward(){
    auto index = m_index;
    ++m_index;
    return at(index);
}

Char CharMngr::backward(){
    auto index =m_index;
    --m_index;
    return at(index);
}

crString CharMngr::str() const{
    return m_str;
}

void CharMngr::seek(SeekOption option, int offset){
    switch(option){
        case Set:
            m_index = offset;
            break;
        case Cur:
            m_index += offset;
            break;
        case End:
            m_index = (m_str.size() > 0) ? m_str.size() - 1 : 0;
            m_index += offset;
            break;
        default:
            break;
    }
}

CSC_END