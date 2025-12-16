#include <cassert>
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

void TokenHolder::addToken(const TokenPtr &token){
    tokens_.push_back(token);
}

Token& TokenHolder::token(){
    assert(tokens_.size() > 0);
    return *(tokens_.at(0));
}

Token& TokenHolder::tokenAt(int index){
    return *(tokens_.at(index));
}

bool TokenHolder::plural() const noexcept{
    return plural_;
}

bool TokenHolder::empty() const noexcept{
    return tokens_.empty();
}

Size_t TokenHolder::size() const noexcept{
    return tokens_.size();
}

CSC_END