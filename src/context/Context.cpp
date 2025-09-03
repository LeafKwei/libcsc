#include <cassert>
#include "csc/types.hpp"
#include "csc/context/Context.hpp"
CSC_BEGIN

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

ConstStr Context::scopeName(){
    return m_current -> name;
}

Context::Pos Context::postion(){
    return Pos{m_current};
}
void Context::setPostion(const Pos &pos){
    if(pos.scope.expired()){
        throw ContextExcept(std::string("Invalid scope postion."));
    }

    m_current = pos.scope.lock();
}

CscStr Context::relation(ConstStr separator){
    std::stringstream stream;
    do_relation(m_current, stream, separator);
    return stream.str();
}

Context& Context::makeVariable(ConstStr name, ConstStr value, ValueType type){
    return makeVariable(name, {value}, type);
}

Context& Context::makeVariable(ConstStr name, InitValues values, ValueType type){
    if(values.size() == 0) throw ContextExcept(std::string("No value specified for variable: ") + name);

    auto iterator = m_current -> variables.find(name);
    if(iterator != m_current -> variables.end()){
        do_setVariable(iterator -> second, values, type);
        return *this;
    }

    do_makeVariable(name, values, type);
    return *this;
}

Context& Context::cleanVariable(ConstStr name){
    if(!probeVariable(name)){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    do_cleanVariable(name);
    return *this;
}

Context::Value Context::getValue(ConstStr name){
    auto iterator = m_current -> variables.find(name);
    if(iterator == m_current -> variables.end()){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    auto variable = iterator -> second;
    assert(variable -> values.size() > 0);
    return {variable -> values.at(0), variable -> type};
}

Context::Values Context::getValues(ConstStr name){
    auto iterator = m_current -> variables.find(name);
    if(iterator == m_current -> variables.end()){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    auto variable = iterator -> second;
    return Values(variable -> values, variable -> type);
}

bool Context::probeVariable(ConstStr name){
    return (m_current -> variables.find(name)) != (m_current -> variables.end());
}

Context& Context::extendValues(ConstStr name, InitValues values){
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

    m_root = std::make_shared<Scope>();
    m_root -> name = "/";
    m_current = m_root;
}

void Context::iterate(ContextSeeker &seeker){
    do_iterate(m_current, seeker);
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

void Context::do_cleanVariable(ConstStr name){
    m_current -> variables.erase(name);
}

void Context::do_makeVariable(ConstStr name, InitValues values, ValueType type){
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
 * Iterate a scope(default current scope), passing scope name to ContextSeeker::enterScope, then passing ever varaible's 
 * name, value and type in the scope to ContextSeeker::values. finally, passing scope name to ContextSeeker::leaveScope when
 * all variables in the socpe are be iterated. 
 */
void Context::do_iterate(ScopePtr scope, ContextSeeker &seeker){
    if(scope != m_root){                                 //Ignore root name.
        seeker.enterScope(scope -> name);
    }

    /* For ever variables in the scope, passing the variable's name, value and type to ContextSeeker::values */
    auto &variables = scope -> variables;
    if(variables.size() != 0){
        for(auto &variable : variables){
            seeker.values(variable.second -> name, Values(variable.second -> values, variable.second -> type));
        }
    }

    /* Iterating child scopes of current scope. */
    auto &scopes = scope -> scopes;
    if(scopes.size() != 0){
        for(auto &scope : scopes){
            do_iterate(scope.second, seeker);
        }
    }

    if(scope != m_root){
        seeker.leaveScope(scope -> name);
    }
}

void Context::do_relation(ScopePtr scope, std::stringstream &stream, ConstStr separator){
    auto current = scope;

    while(!(current -> parent.expired())){
        
    }

    if(scope -> parent.expired()){   //Don't put root scope's name.
        return;
    }

    do_relation(scope -> parent.lock(), stream, separator);
    stream << scope -> name;

    if(scope != m_current){
        stream << separator;
    }
}

CSC_END