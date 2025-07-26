#include "dbc/lex/CharMngr.hpp"
DBC_BEGIN

CharMngr::CharMngr(const Dstring &raw ) : m_raw(raw){
    m_index = 0;
    m_colNumber = 0;
    m_rowNumber = 0;
    m_indexFlag = true;
}

int CharMngr::numberOfCol() const noexcept{

}

int CharMngr::numberOfRow() const noexcept{

}

Dchar CharMngr::pick() noexcept{

}

Dchar CharMngr::tryPick() const noexcept{

}

void CharMngr::forward(int value=1) noexcept{

}

void CharMngr::backward(int value=1) noexcept{

}

bool CharMngr::hasMore() const noexcept{

}

void CharMngr::setIndexFlag(bool flag) noexcept{
    m_indexFlag = flag;
}


DBC_END