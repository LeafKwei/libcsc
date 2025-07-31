#ifndef DBC_LOCATOR_HPP
#define DBC_LOCATOR_HPP

#include "dbc/dbc.hpp"
#include "dbc/alias.hpp"
DBC_BEGIN

class Locator{
public:
    Locator(const Dstring &str, int index);
    int numberOfRow() const;
    int numberOfCol() const;
    int index() const;

private:
    int m_row;
    int m_col;
    int m_index;
};

DBC_END
#endif