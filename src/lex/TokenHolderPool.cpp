#include "csc/lex/TokenHolderPool.hpp"
CSC_BEGIN


TokenHolder& TokenHolderPool::useLastHolder(){
    return *(holderlist_.back().get());
}

TokenHolderPool::HolderPtr TokenHolderPool::takeFirstHolder(){
    auto holder = holderlist_.front();
    holderlist_.erase(holderlist_.begin());
    return holder;
}

Size_t TokenHolderPool::size() const noexcept{
    return holderlist_.size();
}

bool TokenHolderPool::empty() const noexcept{
    return holderlist_.empty();
}

void TokenHolderPool::clear(){
    holderlist_.clear();
}


CSC_END