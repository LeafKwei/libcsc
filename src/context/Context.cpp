#include "csc/types.hpp"
#include "csc/context/Context.hpp"
CSC_BEGIN

Context::Context() : m_idCounter(1){           //作用域ID从1开始，0作为保留ID，为将来的全局Action做准备
    clean();
}

Context& Context::makeScope(crString name, bool entered){
    if(probeScope(name)){
        throw ContextExcept("Can't make repetitive scope.");
    }

    do_makeScope(name);

    if(entered){
        enterScope(name);
    }

    return *this;
}

Context& Context::enterScope(crString name, bool created){
    if(!probeScope(name)){
        if(!created){
            throw ContextExcept(std::string("No such scope: ") + name);
        }

        makeScope(name);
    }

    do_enterScope(name);
    return *this;
}

Context& Context::leaveScope(){
    if(m_current -> parent.expired()){
        throw ContextExcept(std::string("Can't leave from root scope."));
    }

    do_leaveScope();
    return *this;
}

Context& Context::cleanScope(crString name){
    if(!probeScope(name)){
        throw ContextExcept(std::string("No such scope: ") + name);
    }

    do_cleanScope(name);
    return *this;
}   

bool Context::probeScope(crString name) const{
    return (m_current -> scopes.find(name)) != (m_current -> scopes.end());
}   

bool Context::isRootScope() const{
    return !(m_current -> parent.expired());
}

Context::crScopeMeta Context::scopeMetaData() const noexcept{
    return m_current -> meta;
}

Context::Pos Context::postion() const{
    return Pos{m_current};
}

Detector Context::detector(bool absoluted) const{
    return absoluted ? Detector(m_root) : Detector(m_current);
}

void Context::setPostion(const Pos &pos){
    if(pos.scope.expired()){
        throw ContextExcept(std::string("Expired scope postion."));
    }

    m_current = pos.scope.lock();
}

String Context::relation(crString separator) const{
    std::stringstream stream;
    do_relation(m_current, stream, separator);
    return stream.str();
}

Context& Context::makeVariable(crString name, ValueType type, crValue value){
    return makeVariable(name, type, {value});
}

Context& Context::makeVariable(crString name, ValueType type, InitValues values){
    /* 变量存在时，替换原变量值和类型 */
    auto iterator = m_current -> variables.find(name);
    if(iterator != m_current -> variables.end()){
        do_setVariable(iterator -> second, values, type);
        return *this;
    }

    /* 否则创建新变量 */
    do_makeVariable(name, values, type);
    return *this;
}

Context& Context::cleanVariable(crString name){
    if(!probeVariable(name)){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    do_cleanVariable(name);
    return *this;
}

Context::Unit Context::getValueUnit(crString name) const{
    auto iterator = m_current -> variables.find(name);
    if(iterator == m_current -> variables.end()){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    /* 当变量中存在值时，返回首个值，如果变量不存在任何值(空变量)，则返回变量类型对应的零值 */
    auto variable = iterator -> second;
    return (variable -> values.size() > 0) ? 
        Unit{variable -> values.at(0), variable -> type} : 
        Unit{ValueMaker::makeZero(variable -> type), variable -> type};
}

Context::Accessor Context::getValueAccessor(crString name) const{
    auto iterator = m_current -> variables.find(name);
    if(iterator == m_current -> variables.end()){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    auto variable = iterator -> second;
    return ValueAccessor(variable -> values, variable -> type);
}

bool Context::probeVariable(crString name) const{
    return (m_current -> variables.find(name)) != (m_current -> variables.end());
}

Context& Context::extendValues(crString name, InitValues values){
    auto iterator = m_current -> variables.find(name);
    if(iterator == m_current -> variables.end()){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    auto variable = iterator -> second;
    for(auto &value : values){
        variable -> values.push_back(value);
    }
    
    return *this;
}
                                                        
Context& Context::restart(){
    m_current = m_root;
    return *this;
}

void Context::clean(){
    m_root = nullptr;
    m_current = nullptr;
    m_idCounter = 1;

    m_root = std::make_shared<Scope>();
    m_root -> meta = {nextID(), "/", m_root};
    m_current = m_root;
}

void Context::iterate(ContextSeeker &seeker) const{
    do_iterate(m_current, seeker);
}

void Context::do_makeScope(crString name){
    auto scope = std::make_shared<Scope>();
    scope -> meta = {nextID(), name, scope};
    scope -> parent = m_current;
    m_current -> scopes.insert({name, scope});
}

void Context::do_enterScope(crString name){
    m_current = (m_current -> scopes.find(name)) -> second;
}

void Context::do_leaveScope(){
    m_current = m_current -> parent.lock();
}

void Context::do_cleanScope(crString name){
    m_current -> scopes.erase(name);
}

void Context::do_cleanVariable(crString name){
    m_current -> variables.erase(name);
}

void Context::do_makeVariable(crString name, InitValues values, ValueType type){
    auto variable = std::make_shared<Variable>();
    variable -> name = name;
    variable -> type = type;

    for(const auto &value : values){
        variable -> values.push_back(value);
    }

    m_current -> variables.insert({name, variable});
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
    if(scope != m_root){                                 //不传递根作用域的名称
        seeker.enterScope(scope -> meta.id, scope -> meta.name);
    }

    /* 迭代作用域中的每个变量，将变量名称、值列表、类型传递给values函数 */
    auto &variables = scope -> variables;
    if(variables.size() != 0){
        for(auto &variable : variables){
            seeker.values(variable.second -> name, ValueAccessor(variable.second -> values, variable.second -> type));
        }
    }

    /* 迭代所有子作用域 */
    auto &scopes = scope -> scopes;
    if(scopes.size() != 0){
        for(auto &scope : scopes){
            do_iterate(scope.second, seeker);
        }
    }

    if(scope != m_root){
        seeker.leaveScope(scope -> meta.id, scope -> meta.name);
    }
}

void Context::do_relation(ScopePtr scope, std::stringstream &stream, crString separator) const{
    if(scope -> parent.expired()){   //忽略根作用域的名称
        return;
    }

    do_relation(scope -> parent.lock(), stream, separator);
    stream << scope -> meta.name;

    if(scope != m_current){
        stream << separator;
    }
}

CSC_END