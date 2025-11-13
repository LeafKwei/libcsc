#include <cassert>
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

TokenHolder::TokenHolder(){
    tokenlist_.emplace_back();
}

Token& TokenHolder::TokenHolder::newToken(){
    return tokenlist_.emplace_back();
}

Token& TokenHolder::firstToken(){
    assert(tokenlist_.size() > 0);
    return tokenlist_.at(0);
}

Token& TokenHolder::tokenAt(int index){
    return tokenlist_.at(index);
}

Size_t TokenHolder::size() const noexcept{
    return tokenlist_.size();
}

TokenHolder::Type TokenHolder::type() const noexcept{
    return type_;
}

CSC_END