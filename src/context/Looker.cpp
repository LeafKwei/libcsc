#include  "csc/types.hpp"
#include "csc/context/Looker.hpp"
CSC_BEGIN

Looker::Looker(ScopePtr scop) 
    : result_(true)
    , scope_(scop)
    , current_(scope_)
{

}

Looker::Looker(ScopePos pos)
    : result_(true)
    , scope_(pos.ptr)
    , current_(scope_)
{

}

Looker& Looker::looksco(const String &name){
    if(!result_) return *this;      //如果查找过程中已经出现不存在的scope或变量，则停止后续动作

    auto scop = lockScopePtr();
    auto target = scop -> findScope(name);
    if(target == nullptr){
        result_ = false;
        return *this;
    }

    current_ = target;
    return *this;
}

Looker& Looker::lookvar(const String &name) {
    if(!result_) return *this;

    auto scop = lockScopePtr();
    auto target = scop -> findVariable(name);
    if(target == nullptr){
        result_ = false;
        return *this;
    }

    return *this;
}

bool Looker::done() const{
    return result_;
}

void Looker::reset(){
    current_ = scope_;
    result_ = true;
}

ScopePtr Looker::lockScopePtr() const{
    if(current_.expired()){
        throw ContextExcept("Scope weakptr has expired.");
    }

    return current_.lock();
}

CSC_END