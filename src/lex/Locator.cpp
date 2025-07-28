#include "dbc/lex/Locator.hpp"
DBC_BEGIN

Locator::Locator(const Dstring &str, int index) : 
    m_row(0), m_col(0), m_index(index)
{
    decltype(str.size()) start = 0;
    decltype(str.size()) end = index + 1;
    end = end > str.size() ? str.size() : end;

    for(; start < end; start++){
        ++m_col;
        if(str.at(start) == '\n'){
            m_col = 0;
            ++m_row;
        }
    }
}

int Locator::numberOfRow() const noexcept{
    return m_row;
}

int Locator::numberOfCol() const noexcept{
    return m_col;
}

int Locator::index() const noexcept{
    return m_index;
}

DBC_END