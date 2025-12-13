#ifndef CSC_LOCATOR_HPP
#define CSC_LOCATOR_HPP

#include "csc/csc.hpp"
#include "csc/alias.hpp"
CSC_BEGIN

class Locator{
public:
    Locator(const String &str, int index);
    int col() const;
    int row() const;
    int index() const;

private:
    int m_row;
    int m_col;
    int m_index;
};

CSC_END
#endif