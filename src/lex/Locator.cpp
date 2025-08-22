#include "csc/lex/Locator.hpp"
CSC_BEGIN

Locator::Locator(const CscStr &str, int index) : 
    m_row(1), m_col(1), m_index(index)
{
    decltype(str.size()) start = 0;
    decltype(str.size()) end = index;
    end = end > str.size() ? str.size() : end;

    for(; start < end; start++){
        ++m_col;
        if(str.at(start) == '\n'){
            m_col = 1;
            ++m_row;
        }
    }
}

int Locator::col() const{
    return m_col;
}

int Locator::row() const{
    return m_row;
}

int Locator::index() const{
    return m_index;
}

CSC_END