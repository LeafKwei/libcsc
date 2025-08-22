#include "dbc/types.hpp"
#include "dbc/context/Context.hpp"
DBC_BEGIN

Context::Context(){
    clean();
}

Context& Context::makeScope(ConstStr name, bool entered){
    if(probeScope(name)){
        throw ContextExcept("Can't make repetitive scope.");
    }

    do_makeScope(name);

    if(entered){
        enterScope(name);
    }

    return *this;
}

Context& Context::enterScope(ConstStr name, bool created){
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

Context& Context::cleanScope(ConstStr name){
    if(!probeScope(name)){
        throw ContextExcept(std::string("No such scope: ") + name);
    }

    do_cleanScope(name);
    return *this;
}   

bool Context::probeScope(ConstStr name){
    return (m_current -> scopes.find(name)) != (m_current -> scopes.end());
}   

bool Context::isAtRootScope(){
    return !(m_current -> parent.expired());
}   

ConstStr  Context::scopeName(){
    return m_current -> name;
}                                         

Context& Context::makeVariable(ConstStr name, ConstStr value, ValueType type){
    if(probeVariable(name)){
        do_setVariable(name, value, type);
        return *this;
    }

    do_makeVariable(name, value, type);
    return *this;
}

Context& Context::cleanVariable(ConstStr name){
    if(!probeVariable(name)){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    do_cleanVariable(name);
    return *this;
}   

ConstVar Context::getVariable(ConstStr name){
    if(!probeVariable(name)){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    return *((m_current -> variables.find(name)) -> second);
}

bool Context::probeVariable(ConstStr name){
    return (m_current -> variables.find(name)) != (m_current -> variables.end());
}                       
                                                        
Context& Context::restart(){
    m_current = m_root;
    return *this;
}

Context& Context::clean(){
    m_root = nullptr;
    m_current = nullptr;

    m_root = std::make_shared<Scope>();
    m_root -> name = "/";
    m_current = m_root;

    return *this;
}

void Context::do_makeScope(ConstStr name){
    auto scope = std::make_shared<Scope>();
    scope -> name = name;
    scope -> parent = m_current;
    m_current -> scopes.insert({name, scope});
}

void Context::do_enterScope(ConstStr name){
    m_current = (m_current -> scopes.find(name)) -> second;
}

void Context::do_leaveScope(){
    m_current = m_current -> parent.lock();
}

void Context::do_cleanScope(ConstStr name){
    m_current -> scopes.erase(name);
}

void Context::do_makeVariable(ConstStr name, ConstStr value, ValueType type){
    auto variable = std::make_shared<Variable>();
    variable -> name = name;
    variable -> value = value;
    variable -> type = type;
    m_current -> variables.insert({name, variable});
}

void Context::do_cleanVariable(ConstStr name){
    m_current -> variables.erase(name);
}

void Context::do_setVariable(ConstStr name, ConstStr value, ValueType type){
    auto variable = (m_current -> variables.find(name)) -> second;
    variable -> value = value;
    variable -> type = type;
}

DBC_END