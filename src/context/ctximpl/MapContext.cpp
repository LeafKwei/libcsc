#include "csc/types.hpp"
#include "csc/context/ctximpl/MapContext.hpp"
CSC_BEGIN

MapContext::MapContext() : idCounter_(1){           //作用域ID从1开始，0作为保留ID，为将来的全局Action做准备
    clean();
}

MapContext& MapContext::makeScope(const String &name, bool entered){
    if(hasScope(name)){
        throw ContextExcept("Can't make repetitive scope.");
    }

    do_makeScope(name);

    if(entered){
        enterScope(name);
    }

    return *this;
}

MapContext& MapContext::enterScope(const String &name, bool created){
    if(!hasScope(name)){
        if(!created){
            throw ContextExcept(std::string("No such scope: ") + name);
        }

        makeScope(name);
    }

    do_enterScope(name);
    return *this;
}

MapContext& MapContext::leaveScope(){
    if(current_ -> parent.expired()){
        throw ContextExcept(std::string("Can't leave from root scope."));
    }

    do_leaveScope();
    return *this;
}

MapContext& MapContext::cleanScope(const String &name){
    if(!hasScope(name)){
        throw ContextExcept(std::string("No such scope: ") + name);
    }

    do_cleanScope(name);
    return *this;
}   

bool MapContext::hasScope(const String &name) const{
    return (current_ -> scopes.find(name)) != (current_ -> scopes.end());
}   

bool MapContext::isRootScope() const{
    return !(current_ -> parent.expired());
}

const ScopeMetaData& MapContext::scopeMetaData() const noexcept{
    return current_ -> meta;
}

MapContext::Pos MapContext::postion() const{
    return Pos{current_};
}

void MapContext::setPostion(const Pos &pos){
    if(pos.scope.expired()){
        throw ContextExcept(std::string("Expired scope postion."));
    }

    current_ = pos.scope.lock();
}

Querier MapContext::querier(bool absolute) const{
    return (absolute) ? Querier{root_} : Querier{current_};
}

Querier MapContext::querier(const String &name) const{
    auto pos = current_ -> scopes.find(name);
    if(pos == current_ -> scopes.end()){
        throw ContextExcept(std::string("No such scope: ") + name);
    }

    return Querier(pos -> second);
}

MapContext& MapContext::makeVariable(const String &name, ValueType type, const Value &value){
    return makeVariable(name, type, {value});
}

MapContext& MapContext::makeVariable(const String &name, ValueType type, InitValues values){
    /* 变量存在时，替换原变量值和类型 */
    auto iterator = current_ -> variables.find(name);
    if(iterator != current_ -> variables.end()){
        do_setVariable(iterator -> second, values, type);
        return *this;
    }

    /* 否则创建新变量 */
    do_makeVariable(name, values, type);
    return *this;
}

MapContext& MapContext::cleanVariable(const String &name){
    if(!hasVariable(name)){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    do_cleanVariable(name);
    return *this;
}

MapContext::Unit MapContext::getValueUnit(const String &name) const{
    Querier querier(current_);

    if(!querier.hasVariable(name)){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    return querier.directValue(name);
}

bool MapContext::hasVariable(const String &name) const{
    return (current_ -> variables.find(name)) != (current_ -> variables.end());
}

MapContext& MapContext::extendValue(const String &name, const Value &value){
    return extendValues(name, {value});
}

MapContext& MapContext::extendValues(const String &name, InitValues values){
    auto iterator = current_ -> variables.find(name);
    if(iterator == current_ -> variables.end()){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    auto variable = iterator -> second;
    for(auto &value : values){
        variable -> values.push_back(value);
    }
    
    return *this;
}
                                                        
MapContext& MapContext::restart(){
    current_ = root_;
    return *this;
}

void MapContext::clean(){
    root_ = nullptr;
    current_ = nullptr;
    idCounter_ = 1;

    root_ = std::make_shared<Scope>();
    root_ -> meta = {nextID(), "/", root_};
    current_ = root_;
}

void MapContext::iterate(ContextSeeker &seeker) const{
    do_iterate(current_, seeker);
}

void MapContext::do_makeScope(const String &name){
    auto scope = std::make_shared<Scope>();
    scope -> meta = {nextID(), name, scope};
    scope -> parent = current_;
    current_ -> scopes.insert({name, scope});
}

void MapContext::do_enterScope(const String &name){
    current_ = (current_ -> scopes.find(name)) -> second;
}

void MapContext::do_leaveScope(){
    current_ = current_ -> parent.lock();
}

void MapContext::do_cleanScope(const String &name){
    current_ -> scopes.erase(name);
}

void MapContext::do_cleanVariable(const String &name){
    current_ -> variables.erase(name);
}

void MapContext::do_makeVariable(const String &name, InitValues values, ValueType type){
    auto variable = std::make_shared<Variable>();
    variable -> name = name;
    variable -> type = type;

    for(const auto &value : values){
        variable -> values.push_back(value);
    }

    current_ -> variables.insert({name, variable});
}

void MapContext::do_setVariable(VariablePtr variable, InitValues values, ValueType type){
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
void MapContext::do_iterate(ScopePtr scope, ContextSeeker &seeker) const{
    if(scope != root_){                                 //不传递根作用域的名称
        seeker.enterScope(scope -> meta.id, scope -> meta.name);
    }

    /* 迭代作用域中的每个变量，将变量名称、值列表、类型传递给values函数 */
    auto &variables = scope -> variables;
    if(variables.size() != 0){
        for(auto &variable : variables){
            Querier querier(scope);
            querier.captureVariable(variable.second -> name);
            seeker.values(variable.second -> name, querier);
        }
    }

    /* 迭代所有子作用域 */
    auto &scopes = scope -> scopes;
    if(scopes.size() != 0){
        for(auto &scope : scopes){
            do_iterate(scope.second, seeker);
        }
    }

    if(scope != root_){
        seeker.leaveScope(scope -> meta.id, scope -> meta.name);
    }
}

CSC_END