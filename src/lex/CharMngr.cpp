#include "csc/lex/CharMngr.hpp"
CSC_BEGIN

CharMngr::CharMngr(const String &str, Index_t index) : str_(str), index_(index){
    Index_t size = str_.size();
    if(index_ < 0) index_ = 0;
    else if(index_ > size) index_ = size;
}

Index_t CharMngr::index() const noexcept{
    return index_;
}

Size_t CharMngr::length() const noexcept{
    return str_.size();
}

Size_t CharMngr::surplus() const noexcept{
    return (str_.size() - index_);
}

bool CharMngr::valid() const noexcept{
    Index_t size = str_.size();
    return (index_ >= 0) && (index_ < size);
}

Char CharMngr::at(Index_t index) const{
    return str_.at(index);
}

Char CharMngr::near(Offset_t offset) const{
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