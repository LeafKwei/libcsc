#include "csc/types.hpp"
#include "csc/context/ScoQuerier.hpp"
CSC_BEGIN

ScoQuerier::ScoQuerier(ScopePtr scop) : scope_(scop){

}

ScoQuerier::ScoQuerier(ScopePos pos) : scope_(pos.ptr){

}

bool ScoQuerier::noscopes() const{
    return lockScopePtr() -> noscopes();
}

bool ScoQuerier::novariables() const{
    return lockScopePtr() -> novariables();
}

String ScoQuerier::name() const{
    return lockScopePtr() -> scopeinf().name;
}

Size_t ScoQuerier::sizeofVariables() const{
    return lockScopePtr() -> sizeofVariables();
}

Size_t ScoQuerier::sizeofScopes() const{
    return lockScopePtr() -> sizeofScopes();
}

VarQuerier ScoQuerier::varquerier(int index) const{
    return VarQuerier(lockScopePtr() -> variable(index));
}

ScoQuerier ScoQuerier::scoquerier(int index) const{
    return ScoQuerier(lockScopePtr() -> scope(index));
}

ScopePtr ScoQuerier::lockScopePtr() const{
    if(scope_.expired()){
        throw ContextExcept("Scope weakptr has expired.");
    }

    return scope_.lock();
}

CSC_END