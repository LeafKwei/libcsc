#ifndef CSC_CONTEXT_HPP
#define CSC_CONTEXT_HPP

#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/ContextSeeker.hpp"
CSC_BEGIN


/**
 * Context是一个基于std::map的容器，用于保存作用域Scope。
 * 作用域Scope同样是一个基于std::map的容器，用于保存Variable。
 * 变量Variable是由名称name和值value组成的一个键值对，name和value两者都是字符串。一个变量可以拥有多个值。
 * 
 * 当创建一个Context对象时，会默认创建一个根作用域，将其指针保存到成员m_root中，同时m_current也被设置为m_root，表示当前作用域
 * 为根作用域。Context中的所有操作都是基于当前作用域(m_current)进行。
 */
class Context{
public:
    using Value        = VariableValue;
    using Values      = VariableValues;
    using Pos           = ScopePos;
    using InitValues = std::initializer_list<CscStr>;

public:
    Context();
    Context(const Context &other) =delete;
    Context& operator=(const Context &other) =delete;

    Context& makeScope(ConstStr name, bool entered=false);  /* 在当前作用域中创建一个它的子作用域。如果entered为true，那么创建该作用域后将直接进入 */
    Context& enterScope(ConstStr name, bool created=false);  /* 进入当前作用域中的一个子作用域，如果created为true，那么在该作用域不存在时将创建 */ 
    Context& leaveScope();                                                         /* 离开当前作用域，返回到它的父作用域中 */
    Context& cleanScope(ConstStr name);                                 /* 删除当前作用域的一个子作用域，同时也删除其中的所有变量及该子作用域的子作用域 */
    bool         probeScope(ConstStr name) const;                      /* 如果当前作用域中存在指定名称的子作用域，则返回true */
    bool         isRootScope() const;                                             /* 如果当前作用域是根作用域，返回true */
    ConstStr   scopeName() const noexcept;                              /* 获取当前作用域的名称 */
    UID           scopeID() const noexcept;                                    /* 获取当前作用域的id */                         
    Pos           postion() const;                                                     /* 获取当前作用域的Pos对象(对指针的包装) */
    void          setPostion(const Pos &pos);                                /* 将当前作用域设置为pos所指定的作用域 */
    CscStr       relation(ConstStr separator=" ") const;               /* 获取从根作用域到当前作用域之间经过的每个作用域的名称组成的字符串，separator用于指定分隔符 */

    Context& makeVariable(ConstStr name, ConstStr value, ValueType type=ValueType::Unknown);     /* 在当前作用域创建一个变量，如果变量存在，则设置该变量的值和类型 */
    Context& makeVariable(ConstStr name, InitValues values, ValueType type=ValueType::Unknown); /* 在当前作用域创建变量时一次性设置多个值 */
    Context& cleanVariable(ConstStr name);                               /* 删除一个当前作用域中的变量 */
    Value        getValue(ConstStr name) const;                             /* 获取一个当前作用域的变量的值 */
    Values      getValues(ConstStr name) const;                            /* 获取一个当前作用域的变量的Values对象，可按索引获取变量的每个值 */
    bool         probeVariable(ConstStr name) const;                     /* 如果当前作用域存在指定名称的变量，则返回true */
    Context& extendValues(ConstStr name, InitValues values);   /* 向指定名称的变量中追加值 */
                                                          
    Context& restart();                                                                /* 返回到根作用域，即设置当前作用域为根作用域 */
    void clean();                                                                           /* 清除所有的作用域和变量，随后重新创建一个新的根作用域 */
    void iterate(ContextSeeker &seeker) const;                         /* 从当前作用域开始，按DFS迭代其中的每个变量及每个子作用域 */

private:
    UID         m_idCounter;
    ScopePtr m_root;
    ScopePtr m_current;

    inline UID nextID() noexcept;
    void do_makeScope(ConstStr name);
    void do_enterScope(ConstStr name);
    void do_leaveScope();
    void do_cleanScope(ConstStr name);
    void do_makeVariable(ConstStr name, InitValues values, ValueType type);
    void do_cleanVariable(ConstStr name);
    void do_setVariable(VariablePtr variable, InitValues values, ValueType type);
    void do_iterate(ScopePtr scope, ContextSeeker &seeker) const;
    void do_relation(ScopePtr scope, std::stringstream &stream, ConstStr separator) const;
};

inline UID Context::nextID() noexcept{
    return m_idCounter++;
}

CSC_END
#endif