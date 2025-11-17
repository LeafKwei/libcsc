#include <cassert>
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

void TokenHolder::pushToken(const Token &token){
    tokenlist_.push_back(token);
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

bool TokenHolder::empty() const noexcept{
    return tokenlist_.empty();
}


CSC_END