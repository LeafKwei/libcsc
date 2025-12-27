#ifndef CSC_CONTEXT_HPP
#define CSC_CONTEXT_HPP

#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/ContextSeeker.hpp"
#include "csc/context/Querier.hpp"
#include "csc/context/Scope.hpp"
CSC_BEGIN

template<typename Scp, typename = IsScopeType<Scp>>
class Context{
public:
    using ScopeType         = Scp;
    using Unit                    = ValueUnit;
    using Pos                     = ScopePos;
    using InitValues           = std::initializer_list<Value>;

public:
    Context();
    Context(const Context &other) =delete;
    Context& operator=(const Context &other) =delete;

    Context&  makeScope(const String &name, bool entered=false);  
    Context&  enterScope(const String &name, bool created=false);    
    Context&  leaveScope();                                                                   
    Context&  cleanScope(const String &name);                                   
    bool          hasScope(const String &name) const;                        
    bool          isRootScope() const;                                                         
    Pos            postion() const;                                                                 
    void           setPostion(const Pos &pos);                                             
    Querier      querier(bool absolute=false) const;                                
    Querier      querier(const String &name) const;                                

    Context&   makeVariable(const String &name, ValueType type, const Value &value);      
    Context&   makeVariable(const String &name, ValueType type, InitValues values); 
    Context&   cleanVariable(const String &name);                                 
    Unit            getValueUnit(const String &name) const;                       
    bool           hasVariable(const String &name) const;                     
    Context&   extendValue(const String &name, const Value &value);              
    Context&   extendValues(const String &name, InitValues values);                                                          
    Context&   restart();                                                                
    void            clean();                                                                  
    void            iterate(ContextSeeker &seeker) const;
    ScopeInf     scopeinf() const;

private:
    UID         idCounter_;
    ScopePtr root_;
    ScopePtr current_;

    inline UID nextID() noexcept;
    void do_makeScope(const String &name);
    void do_enterScope(const String &name);
    void do_leaveScope();
    void do_cleanScope(const String &name);
    void do_makeVariable(const String &name, InitValues values, ValueType type);
    void do_cleanVariable(const String &name);
    void do_setVariable(VariablePtr variable, InitValues values, ValueType type);
    void do_iterate(ScopePtr scope, ContextSeeker &seeker) const;
};

template<typename Scp, typename Eab>
inline Context<Scp, Eab>::Context() : idCounter_(1){           //作用域ID从1开始，0作为保留ID，为将来的全局Action做准备
    clean();
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::makeScope(const String &name, bool entered){
    if(hasScope(name)){
        throw ContextExcept("Can't make repetitive scope.");
    }

    do_makeScope(name);

    if(entered){
        enterScope(name);
    }

    return *this;
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::enterScope(const String &name, bool created){
    if(!hasScope(name)){
        if(!created){
            throw ContextExcept(std::string("No such scope: ") + name);
        }

        makeScope(name);
    }

    do_enterScope(name);
    return *this;
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::leaveScope(){
    if(current_ -> parent() == nullptr){
        throw ContextExcept(std::string("Can't leave from root scope."));
    }

    do_leaveScope();
    return *this;
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::cleanScope(const String &name){
    if(!hasScope(name)){
        throw ContextExcept(std::string("No such scope: ") + name);
    }

    do_cleanScope(name);
    return *this;
}

template<typename Scp, typename Eab>
inline bool Context<Scp, Eab>::hasScope(const String &name) const{
    return current_ -> findScope(name) != nullptr;
}   

template<typename Scp, typename Eab>
inline bool Context<Scp, Eab>::isRootScope() const{
    return !(current_ -> parent() != nullptr);
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>::Pos Context<Scp, Eab>::postion() const{
    return Pos{current_};
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::setPostion(const Pos &pos){
    if(pos.ptr.expired()){
        throw ContextExcept(std::string("Expired scope postion."));
    }

    current_ = pos.ptr.lock();
}

template<typename Scp, typename Eab>
inline Querier Context<Scp, Eab>::querier(bool absolute) const{
    return (absolute) ? Querier{root_} : Querier{current_};
}

template<typename Scp, typename Eab>
inline Querier  Context<Scp, Eab>::querier(const String &name) const{
    auto pos = current_ -> scopes.find(name);
    if(pos == current_ -> scopes.end()){
        throw ContextExcept(std::string("No such scope: ") + name);
    }

    return Querier(pos -> second);
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::makeVariable(const String &name, ValueType type, const Value &value){
    return makeVariable(name, type, {value});
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::makeVariable(const String &name, ValueType type, InitValues values){
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

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::cleanVariable(const String &name){
    if(!hasVariable(name)){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    do_cleanVariable(name);
    return *this;
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>::Unit Context<Scp, Eab>::getValueUnit(const String &name) const{
    Querier querier(current_);

    if(!querier.hasVariable(name)){
        throw ContextExcept(std::string("No such variable: ") + name);
    }

    return querier.directValue(name);
}

template<typename Scp, typename Eab>
inline bool Context<Scp, Eab>::hasVariable(const String &name) const{
    return (current_ -> variables.find(name)) != (current_ -> variables.end());
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::extendValue(const String &name, const Value &value){
    return extendValues(name, {value});
}

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::extendValues(const String &name, InitValues values){
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

template<typename Scp, typename Eab>
inline Context<Scp, Eab>& Context<Scp, Eab>::restart(){
    current_ = root_;
    return *this;
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::clean(){
    root_ = nullptr;
    current_ = nullptr;
    idCounter_ = 1;

    root_ = std::make_shared<ScopeType>("/", nextID());
    current_ = root_;
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::iterate(ContextSeeker &seeker) const{
    do_iterate(current_, seeker);
}

template<typename Scp, typename Eab>
inline ScopeInf Context<Scp, Eab>::scopeinf() const{
    return current_ -> scopeinf();
}

////////////////////////////////////////////////////////////////////////////////////////private
template<typename Scp, typename Eab>
inline UID Context<Scp, Eab>::nextID() noexcept{
    return idCounter_++;
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::do_makeScope(const String &name){
    auto scope = std::make_shared<ScopeType>(name, nextID(), current_);
    current_ -> insertScope(name, scope);
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::do_enterScope(const String &name){
    current_ = current_ -> findScope(name);
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::do_leaveScope(){
    current_ = current_ -> parent();
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::do_cleanScope(const String &name){
    current_ -> eraseScope(name);
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::do_cleanVariable(const String &name){
    current_ -> eraseVariable(name);
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::do_makeVariable(const String &name, InitValues values, ValueType type){
    auto variable = std::make_shared<Variable>();
    variable -> name = name;
    variable -> type = type;

    for(const auto &value : values){
        variable -> values.push_back(value);
    }

    current_ -> insertVariable(name, variable);
}

template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::do_setVariable(VariablePtr variable, InitValues values, ValueType type){
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
template<typename Scp, typename Eab>
inline void Context<Scp, Eab>::do_iterate(ScopePtr scope, ContextSeeker &seeker) const{
    if(scope != root_){                                 //不传递根作用域的名称
        seeker.enterScope(scope -> id(), scope -> name());
    }

    /* 迭代作用域中的每个变量，将变量名称、值列表、类型传递给values函数 */
    auto varsize = scope -> sizeofVariables();
    for(Size_t idx = 0; idx < varsize; idx++){
        auto variable = scope -> variable(idx);
        Querier querier(scope);
        querier.captureVariable(variable -> name());
        seeker.values(variable -> name, querier);
    }

    /* 迭代所有子作用域 */
    auto scpsize = scope -> sizeofScopes();
    for(Size_t idx = 0; idx < scpsize; idx++){
        do_iterate(scope -> scope(idx));
    }

    if(scope != root_){
        seeker.leaveScope(scope -> id, scope -> name);
    }
}

CSC_END
#endif