#include <cassert>
#include "csc/types.hpp"
#include "csc/lex/TokenPool.hpp"
CSC_BEGIN

TokenHolder& TokenPool::makeHolder(){
    if(holderptr_ != nullptr) return referHolder();
    holderptr_ = std::make_shared<TokenHolder>();
    return referHolder();
}

TokenHolder& TokenPool::referHolder(){
    assert(holderptr_ != nullptr);
    return *(holderptr_.get());
}

TokenPool::HolderPtr TokenPool::takeFirstHolder(){
    assert(holderlist_.size() > 0);
    auto ptr = holderlist_.front();
    holderlist_.erase(holderlist_.begin());
    return ptr;
}

void TokenPool::saveHolder(){
    if(holderptr_== nullptr) throw LexExcept("Can't save a holderptr pointed to nullptr.");
    holderlist_.push_back(holderptr_);
    holderptr_ = nullptr;
}

bool TokenPool::empty() const noexcept{
    return holderlist_.empty();
}

CSC_END