#include <cassert>
#include "csc/lex/TokenHolder.hpp"
CSC_BEGIN

Token& TokenHolder::token(int index){
    assert(static_cast<Size_t>(index) < tokens_.size());
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

void TokenHolder::addToken(const TokenPtr &token){
    tokens_.push_back(token);
}

void TokenHolder::setPlural(bool plural){
    plural_ = plural;
}

CSC_END