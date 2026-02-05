#include  "csc/types.hpp"
#include "csc/context/RouteLooker.hpp"
CSC_BEGIN

RouteLooker::RouteLooker(ScopePtr scop) 
    : result_(true)
    , scope_(scop)
    , current_(scope_)
{

}

RouteLooker::RouteLooker(ScopePos pos)
    : result_(true)
    , scope_(pos.ptr)
    , current_(scope_)
{

}

RouteLooker& RouteLooker::looksco(const String &name){
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

RouteLooker& RouteLooker::lookvar(const String &name) {
    if(!result_) return *this;

    auto scop = lockScopePtr();
    auto target = scop -> findVariable(name);
    if(target == nullptr){
        result_ = false;
        return *this;
    }

    return *this;
}

bool RouteLooker::done() const{
    return result_;
}

void RouteLooker::reset(){
    current_ = scope_;
    result_ = true;
}

ScopePtr RouteLooker::lockScopePtr() const{
    if(current_.expired()){
        throw ContextExcept("Scope weakptr has expired.");
    }

    return current_.lock();
}

CSC_END