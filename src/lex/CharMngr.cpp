#include "csc/lex/CharMngr.hpp"
CSC_BEGIN

CharMngr::CharMngr(const String &str, int index) : str_(str), index_(index){
    if(index_ < 0) index_ = 0;
    else if(index_ > str_.size()) index_ = str_.size();
}

int CharMngr::index() const noexcept{
    return index_;
}

Size_t CharMngr::length() const noexcept{
    return str_.size();
}

Size_t CharMngr::surplus() const noexcept{
    return (str_.size() - index_);
}

bool CharMngr::valid() const noexcept{
    return (index_ >= 0) && (index_ < str_.size());
}

Char CharMngr::at(int index) const{
    return str_.at(index);
}

Char CharMngr::near(int offset) const{
    return str_.at(index_ + offset);
}

Char CharMngr::getch() const{
    return str_.at(index_);
}

Char CharMngr::forward(){
    auto index = index_;
    ++index_;
    return at(index);
}

Char CharMngr::backward(){
    auto index =index_;
    --index_;
    return at(index);
}

const String& CharMngr::str() const{
    return str_;
}

void CharMngr::seek(SeekOption option, int offset){
    switch(option){
        case Set:
            index_ = offset;
            break;
        case Cur:
            index_ += offset;
            break;
        case End:
            index_ = (str_.size() > 0) ? str_.size() - 1 : 0;
            index_ += offset;
            break;
        default:
            break;
    }
}

CSC_END