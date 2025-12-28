#include "csc/context/impl/ListScope.hpp"
CSC_BEGIN

ListScope::ListScope(const String &name, UID id) : inf_{id, name}{

}

ListScope::ListScope(const String &name, UID id, ScopePtr parent) : inf_{id, name}, parent_(parent){

}

bool ListScope::insertScope(const String &name, ScopePtr sptr){
    scopes_.push_back({name, sptr});
    return true;
}

bool ListScope::insertVariable(const String &name, VariablePtr vptr){
    variables_.push_back({name, vptr});
    return true;
}

bool ListScope::eraseScope(const String &name){
    auto pos = findScopePostion(name);
    if(pos == scopes_.end()){
        return false;
    }

    scopes_.erase(pos);
    return true;
}

bool ListScope::eraseVariable(const String &name){
    auto pos = findVariablePostion(name);
    if(pos == variables_.end()){
        return false;
    }

    variables_.erase(pos);
    return true;
}

ScopePtr ListScope::findScope(const String &name) {
    auto pos = findScopePostion(name);
    if(pos == scopes_.end()){
        return nullptr;
    }

    return pos -> second;
}

ScopePtr ListScope::scope(int index){
    auto pos = std::next(scopes_.begin(), index);
    return pos -> second;
}

VariablePtr ListScope::findVariable(const String &name){
    auto pos = findVariablePostion(name);
    if(pos == variables_.end()){
        return nullptr;
    }

    return pos -> second;
}

VariablePtr ListScope::variable(int index){
    auto pos = std::next(variables_.begin(), index);
    return pos -> second;
}

ScopePtr ListScope::parent(){
    return (parent_.expired()) ? nullptr : parent_.lock();
}

void ListScope::setParent(ScopePtr parent){
    parent_ = parent;
}

Size_t ListScope::sizeofScopes() const noexcept{
    return scopes_.size();
}

Size_t ListScope::sizeofVariables() const noexcept{
    return variables_.size();
}

bool ListScope::noscopes() const noexcept{
    return scopes_.empty();
}

bool ListScope::novariables() const noexcept{
    return variables_.empty();
}

ScopeInf ListScope::scopeinf() const{
    return inf_;
}

ListScope::ScopeList::iterator ListScope::findScopePostion(const String &name){
    for(auto begin = scopes_.begin(); begin != scopes_.end(); begin++){
        if(begin -> first == name){
            return begin;
        }
    }

    return scopes_.end();
}

ListScope::VariableList::iterator ListScope::findVariablePostion(const String &name){
    for(auto begin = variables_.begin(); begin != variables_.end(); begin++){
        if(begin -> first == name){
            return begin;
        }
    }

    return variables_.end();
}

CSC_END