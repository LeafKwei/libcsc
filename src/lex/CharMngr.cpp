#include "dbc/lex/CharMngr.hpp"
DBC_BEGIN

CharMngr::CharMngr(const Dstring &str, int index) : m_str(str), m_index(index){
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

Dchar CharMngr::at(int index) const{
    return m_str.at(index);
}

Dchar CharMngr::getch() const{
    return m_str.at(m_index);
}

Dchar CharMngr::forward(){
    auto index = m_index;
    ++m_index;
    return at(index);
}

Dchar CharMngr::backward(){
    auto index =m_index;
    --m_index;
    return at(index);
}

const Dstring& CharMngr::str() const{
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
            m_index = m_str.size() - 1;
            m_index += offset;
            break;
        default:
            break;
    }
}

DBC_END