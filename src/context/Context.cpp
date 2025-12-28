#include "csc/types.hpp"
#include "csc/context/Context.hpp"
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
            throw ContextExcept(std::string("No such scope: ") + name);
        }

        makeScope(name);
    }

    do_enterScope(name);
    return *this;
}

Context& Context::leaveScope(){
    if(current_ -> parent() == nullptr){
        throw ContextExcept(std::string("Can't leave from root scope."));
    }

    do_leaveScope();
    return *this;
}

Context& Context::cleanScope(const String &name){
    if(!hasScope(name)){
        throw ContextExcept(std::string("No such scope: ") + name);
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
        throw ContextExcept(std::string("Expired scope postion."));
    }

    current_ = pos.ptr.lock();
}

Querier Context::querier(bool absolute) const{
    return (absolute) ? Querier{root_} : Querier{current_};
}

Querier Context::querier(const String &name) const{
    auto scope = current_ -> findScope(name);
    if(scope == nullptr){
        throw ContextExcept(std::string("No such scope: ") + name);
    }

    return Querier(scope);
}

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
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    do_cleanVariable(name);
    return *this;
}

Context::Unit Context::getValueUnit(const String &name) const{
    Querier querier(current_);

    if(!querier.hasVariable(name)){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    return querier.directValue(name);
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
        throw ContextExcept(std::string("No such variable: ") + name);
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

void Context::iterate(ContextSeeker &seeker) const{
    do_iterate(current_, seeker);
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

/**
 * 迭代指定的作用域scope。此函数将按DFS算法对作用域进行迭代，即：
 * 1.传递当前作用域的名称和id到enterScope函数
 * 2.迭代作用域中的每个变量，传递变量信息到values函数
 * 3.检查当前作用域是否有子作用域，如有则将子作用域传递给do_iterate递归
 * 4.迭代所有子作用域后，再将当前作用域的名称和id传递给leaveScope函数
 */
void Context::do_iterate(ScopePtr scope, ContextSeeker &seeker) const{
    if(scope != root_){                                 //不传递根作用域的名称
        const auto &inf = scope -> scopeinf();
        seeker.enterScope(inf.id, inf.name);
    }

    /* 迭代作用域中的每个变量，将变量名称、值列表、类型传递给values函数 */
    auto varsize = scope -> sizeofVariables();
    for(Size_t idx = 0; idx < varsize; idx++){
        Querier querier(scope);
        auto variable = scope -> variable(idx);
        querier.captureVariable(variable ->name);
        seeker.values(variable -> name, querier);
    }

    /* 迭代所有子作用域 */
    auto scopesize = scope -> sizeofScopes();
    for(Size_t idx = 0; idx < scopesize; idx++){
        do_iterate(scope -> scope(idx), seeker);
    }

    if(scope != root_){
        const auto &inf = scope -> scopeinf();
        seeker.leaveScope(inf.id, inf.name);
    }
}

CSC_END