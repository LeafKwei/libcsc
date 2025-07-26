#include "dbc/lex/CharMngr.hpp"
DBC_BEGIN

CharMngr::CharMngr(const Dstring &raw ) : m_raw(raw){
    m_index = 0;
    m_colNumber = 0;
    m_rowNumber = 0;
    m_indexFlag = true;
}

int CharMngr::numberOfCol() const noexcept{
    return m_colNumber;
}

int CharMngr::numberOfRow() const noexcept{
    return m_rowNumber;
}

Dchar CharMngr::pick() noexcept{
    Dchar ch = m_raw.at(m_index);
    m_index += 1;
    return ch;
}

Dstring CharMngr::pickn(unsigned int n) noexcept{
    int len = (m_index + n < m_raw.size()) ? n : (m_raw.size() - m_index);
    int pos = m_index;
    m_index += len;
    return  m_raw.substr(pos, len);
}

Dstring CharMngr::tryPickn(unsigned int n) const noexcept{
    int len = (m_index + n < m_raw.size()) ? n : (m_raw.size() - m_index);
    return  m_raw.substr(m_index, len);
}

Dchar CharMngr::tryPick() const noexcept{
    return m_raw.at(m_index);
}

void CharMngr::forward(unsigned int value=1) noexcept{
    m_index += value;
}

void CharMngr::backward(unsigned int value=1) noexcept{
    m_index -= value;
    m_index = m_index < 0 ? 0 : m_index;
}

bool CharMngr::hasMore() const noexcept{
    return m_index < m_raw.size();
}

DBC_END