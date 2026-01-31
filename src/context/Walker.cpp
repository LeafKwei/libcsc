#include "csc/types.hpp"
#include "csc/context/Walker.hpp"
CSC_BEGIN

Walker::Walker(ScopePtr scop) : scope_(scop){

}

Walker::Walker(ScopePos pos) : scope_(pos.ptr){

}

bool Walker::noscopes() const{
    return lockScopePtr() -> noscopes();
}

bool Walker::novariables() const{
    return lockScopePtr() -> novariables();
}

String Walker::currentName() const{
    return lockScopePtr() -> scopeinf().name;
}

void Walker::startScopeWalk(){
    scoindex_ = 0;
    scosize_ = lockScopePtr() -> sizeofScopes();
}

void Walker::startVariableWalk(){
    varindex_ = 0;
    varsize_ = lockScopePtr() -> sizeofVariables();
}

bool Walker::hasNextScope() const{
    return scoindex_ < scosize_;
}

bool Walker::hasNextVariable() const{
    return varindex_ < varsize_;
} 

Walker Walker::nextScope(){
    return Walker(lockScopePtr() -> scope(scoindex_++));
}

Querier Walker::nextVariable(){
    return Querier(lockScopePtr() -> variable(varindex_++));
}       

ScopePtr Walker::lockScopePtr() const{
    if(scope_.expired()){
        throw ContextExcept("Scope weakptr has expired.");
    }

    return scope_.lock();
}

CSC_END