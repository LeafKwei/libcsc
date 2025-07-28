#ifndef DBC_LOCATOR_HPP
#define DBC_LOCATOR_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

class Locator{
public:
    Locator(const Dstring &str, int index);
    int numberOfRow() const noexcept;
    int numberOfCol() const noexcept;
    int index() const noexcept;

private:
    int m_row;
    int m_col;
    int m_index;
};

DBC_END
#endif