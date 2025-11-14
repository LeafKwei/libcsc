#include <cassert>
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

Token& TokenHolder::tokenAt(int index){
    return tokenlist_.at(index);
}

Size_t TokenHolder::size() const noexcept{
    return tokenlist_.size();
}

TokenHolder::Type TokenHolder::type() const noexcept{
    return type_;
}

void TokenHolder::setType(TokenHolder::Type type){
    type_ = type;
}

CSC_END