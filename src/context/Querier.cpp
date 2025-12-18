#include "csc/types.hpp"
#include "csc/context/val.hpp"
#include "csc/context/Querier.hpp"
CSC_BEGIN

Querier::Querier(ScopePos spos) : scope_(spos.scope){

}

Querier::Querier(ScopePtr scope) : scope_(scope){

}

bool Querier::tryEnter(const String &name){
    auto scopeptr = lockScopePtr();
    auto pos = scopeptr -> scopes.find(name);
    if(pos == scopeptr -> scopes.end()){
        return false;
    }

    scope_ = pos -> second;
    return true;
}

bool Querier::hasScope(const String &name) const{
    auto scopeptr = lockScopePtr();
    auto pos = scopeptr -> scopes.find(name);
    return pos != scopeptr -> scopes.end();
}

bool Querier::hasVariable(const String &name) const{
    auto scopeptr = lockScopePtr();
    auto pos = scopeptr -> variables.find(name);
    return pos != scopeptr -> variables.end();
}

ValueUnit Querier::directValue(const String &name) const{
    auto scopeptr = lockScopePtr();
    auto pos = scopeptr -> variables.find(name);
    auto varptr = pos -> second;

    /* 如果变量中存在值，则返回首个值，否则返回一个该变量类型的零值 */
    return (varptr -> values.size() > 0) ? 
        ValueUnit{varptr -> values.at(0),                 varptr -> type} : 
        ValueUnit{makeZeroValue(varptr -> type), varptr -> type};
}

Querier& Querier::captureVariable(const String &name){
    auto scopeptr = lockScopePtr();
    auto pos = scopeptr -> variables.find(name);
    var_ = pos -> second;
    return *this;
}

ValueType Querier::queryType() const{
    auto varptr = lockVariablePtr();
    return varptr -> type;
}

Size_t Querier::querySize() const{
    auto varptr = lockVariablePtr();
    return varptr -> values.size();
}

ValueUnit Querier::queryValue(int index) const{
    auto varptr = lockVariablePtr();

    /* 如果index在values的大小之内，返回对应位置的值，否则返回一个零值 */
    auto uindex = static_cast<Size_t>(index);
    return (uindex < varptr -> values.size()) ? 
        ValueUnit{varptr -> values.at(index),           varptr -> type} : 
        ValueUnit{makeZeroValue(varptr -> type), varptr -> type};
}

ScopePtr Querier::lockScopePtr() const{
    if(scope_.expired()){
        throw ContextExcept("Scope weakptr has expired.");
    }

    return scope_.lock();
}

VariablePtr Querier::lockVariablePtr() const{
    if(var_.expired()){
        throw ContextExcept("Variable weakptr has expired.");
    }

    return var_.lock();
}

CSC_END