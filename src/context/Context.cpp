#include "csc/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/context/val.hpp"
CSC_BEGIN

Context::Context(ScopeType type) : idCounter_(1), scopetype_(type){           //作用域ID从1开始，0作为保留ID，为将来的全局Action做准备
    clean();
}

Context& Context::makeScope(const String &name, bool entered){
    if(hasScope(name)){
        throw ContextExcept("Can't make repetitive scope.");
    }

    do_makeScope(name);

    if(entered){
        enterScope(name);
    }

    return *this;
}

Context& Context::enterScope(const String &name, bool created){
    if(!hasScope(name)){
        if(!created){
            throw ContextExcept("No such scope: " + name);
        }

        makeScope(name);
    }

    do_enterScope(name);
    return *this;
}

Context& Context::leaveScope(){
    if(current_ -> parent() == nullptr){
        throw ContextExcept("Can't leave from root scope.");
    }

    do_leaveScope();
    return *this;
}

Context& Context::cleanScope(const String &name){
    if(!hasScope(name)){
        throw ContextExcept("No such scope: " + name);
    }

    do_cleanScope(name);
    return *this;
}   

bool Context::hasScope(const String &name) const{
    return (current_ -> findScope(name) != nullptr);
}   

bool Context::isRootScope() const{
    return !(current_ -> parent() != nullptr);
}

ScopeInf Context::scopeinf() const noexcept{
    return current_ -> scopeinf();
}

Context::Pos Context::postion() const{
    return Pos{current_};
}

void Context::setPostion(const Pos &pos){
    if(pos.ptr.expired()){
        throw ContextExcept("Expired scope postion.");
    }

    current_ = pos.ptr.lock();
}

////////////////////////////////////////////////////////////////////////////////////////Querier, Looker, Walker
Querier Context::querier(const String &name) const{
    return Querier(currentFindVarp(name));
}

Looker Context::looker(bool fromroot=false) const{
    return (fromroot) ? Looker(root_) : Looker(current_);
}

Looker Context::looker(const String &name) const{
    return Looker(currentFindScop(name));
}

Walker Context::walker(bool fromroot=false) const{
    return (fromroot) ? Walker(root_) : Walker(current_);
}

Walker Context::walker(const String &name) const{
    return Walker(currentFindScop(name));
}
////////////////////////////////////////////////////////////////////////////////////////

Context& Context::makeVariable(const String &name, ValueType type, const Value &value){
    return makeVariable(name, type, {value});
}

Context& Context::makeVariable(const String &name, ValueType type, InitValues values){
    /* 变量存在时，替换原变量值和类型 */
    auto variable = current_ -> findVariable(name);
    if(variable != nullptr){
        do_setVariable(variable, values, type);
        return *this;
    }

    /* 否则创建新变量 */
    do_makeVariable(name, values, type);
    return *this;
}

Context& Context::cleanVariable(const String &name){
    if(!hasVariable(name)){
        throw ContextExcept("No such variable: " + name);
    }

    do_cleanVariable(name);
    return *this;
}

Context::Unit Context::getValueUnit(const String &name) const{
    auto variable = currentFindVarp(name);
    auto type = variable -> type;
    auto size = variable -> values.size();

    return (size > 0) 
        ? ValueUnit{variable -> values.at(0), type}    //如果变量中存在值，则返回首个值
        : ValueUnit{makeZeroValue(type), type};       //否则返回变量的类型的零值
}

bool Context::hasVariable(const String &name) const{
    return (current_ -> findVariable(name) != nullptr);
}

Context& Context::extendValue(const String &name, const Value &value){
    return extendValues(name, {value});
}

Context& Context::extendValues(const String &name, InitValues values){
    auto variable = current_ -> findVariable(name);
    if(variable == nullptr){
        throw ContextExcept("No such variable: " + name);
    }

    for(auto &value : values){
        variable -> values.push_back(value);
    }
    
    return *this;
}
                                                        
Context& Context::restart(){
    current_ = root_;
    return *this;
}

void Context::clean(){
    root_ = nullptr;
    current_ = nullptr;
    idCounter_ = 1;

    root_ = factory_makeSharedScope(scopetype_, "/", nextID());
    current_ = root_;
}

VariablePtr Context::currentFindVarp(const String &name) const{
    auto variable = current_ -> findVariable(name);
    if(variable == nullptr){
        throw ContextExcept("No such variable: " + name);
    }

    return variable;
}

ScopePtr Context::currentFindScop(const String &name) const{
    auto scope = current_ -> findScope(name);
    if(scope == nullptr){
        throw ContextExcept("No such scope: " + name);
    }
    
    return scope;
}

void Context::do_makeScope(const String &name){
    auto scope = factory_makeSharedScope(scopetype_, name, nextID(), current_);
    current_ -> insertScope(name, scope);
}

void Context::do_enterScope(const String &name){
    current_ = current_ -> findScope(name);
}

void Context::do_leaveScope(){
    current_ = current_ -> parent();
}

void Context::do_cleanScope(const String &name){
    current_ -> eraseScope(name);
}

void Context::do_cleanVariable(const String &name){
    current_ -> eraseVariable(name);
}

void Context::do_makeVariable(const String &name, InitValues values, ValueType type){
    auto variable = std::make_shared<Variable>();
    variable -> name = name;
    variable -> type = type;

    for(const auto &value : values){
        variable -> values.push_back(value);
    }

    current_ -> insertVariable(name, variable);
}

void Context::do_setVariable(VariablePtr variable, InitValues values, ValueType type){
    variable -> values.clear();
    variable -> type = type;

    for(const auto &value : values){
        variable -> values.push_back(value);
    }
}

CSC_END