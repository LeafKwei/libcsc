#include "dbc/lex/CharMngr.hpp"
DBC_BEGIN

CharMngr::CharMngr(const Dstring &raw ) : m_raw(raw){
    m_index = 0;
    m_count = 0;
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
    auto ch = m_raw.at(m_index);
    updateCounter();
    return ch;
}

Dchar CharMngr::tryPick() const noexcept{
    return m_raw.at(m_index);
}

void CharMngr::forward(unsigned int value) noexcept{
    m_index += value;
}

void CharMngr::backward(unsigned int value) noexcept{
    m_index -= value;
    m_index = m_index < 0 ? 0 : m_index;
}

bool CharMngr::hasMore() const noexcept{
    return m_index < m_raw.size();
}

int CharMngr::count() noexcept{
    auto cnt = m_count;
    m_count = 0;
    return cnt;
}

CharsOptor CharMngr::charsoptor() const noexcept{
    return CharsOptor(m_raw, m_index);
}

void CharMngr::updateCounter(unsigned int value) noexcept{
    m_index += value;
    m_count += value;
}

DBC_END