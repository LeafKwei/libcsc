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
    int row_;
    int col_;
    int index_;
};

CSC_END
#endif