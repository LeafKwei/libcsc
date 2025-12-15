#include "csc/lex/Locator.hpp"
CSC_BEGIN

Locator::Locator(const String &str, int index) : 
    row_(1), col_(1), index_(index)
{
    decltype(str.size()) start = 0;
    decltype(str.size()) end = index;
    end = end > str.size() ? str.size() : end;

    for(; start < end; start++){
        ++col_;
        if(str.at(start) == '\n'){
            col_ = 1;
            ++row_;
        }
    }
}

int Locator::col() const{
    return col_;
}

int Locator::row() const{
    return row_;
}

int Locator::index() const{
    return index_;
}

CSC_END