#include "csc/context/impl/MapScope.hpp"
CSC_BEGIN

MapScope::MapScope(const String &name, UID id) : inf_{id, name}{

}

MapScope::MapScope(const String &name, UID id, ScopePtr parent) : inf_{id, name}, parent_(parent){

}

bool MapScope::insertScope(const String &name, ScopePtr sptr){
    return scopes_.insert({name, sptr}).second;
}

bool MapScope::insertVariable(const String &name, VariablePtr vp){
    return variables_.insert({name, vp}).second;
}

bool MapScope::eraseScope(const String &name){
    return scopes_.erase(name) > 0;
}

bool MapScope::eraseVariable(const String &name){
    return variables_.erase(name) > 0;
}

ScopePtr MapScope::findScope(const String &name){
    auto pos = scopes_.find(name);
    if(pos == scopes_.end()){
        return nullptr;
    }

    return pos -> second;
}

ScopePtr MapScope::scope(int index){
    auto pos = std::next(scopes_.begin(), index);
    return pos -> second;
}

VariablePtr MapScope::findVariable(const String &name){
    auto pos = variables_.find(name);
    if(pos == variables_.end()){
        return nullptr;
    }

    return pos -> second;
}

VariablePtr MapScope::variable(int index){
    auto pos = std::next(variables_.begin(), index);
    return pos -> second;
}

ScopePtr MapScope::parent(){
    return (parent_.expired()) ? nullptr : parent_.lock();
}

void MapScope::setParent(ScopePtr parent){
    parent_ = parent;
}

Size_t MapScope::sizeofScopes() const noexcept{
    return scopes_.size();
}

Size_t MapScope::sizeofVariables() const noexcept{
    return variables_.size();
}

bool MapScope::noscopes() const noexcept{
    return scopes_.empty();
}

bool MapScope::novariables() const noexcept{
    return variables_.empty();
}

ScopeInf MapScope::scopeinf() const{
    return inf_;
}

CSC_END