#ifndef CSC_CONTEXT_HPP
#define CSC_CONTEXT_HPP

#include <iostream>
#include <sstream>
#include "csc/csc.hpp"
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/ContextSeeker.hpp"
#include "csc/context/Querier.hpp"
CSC_BEGIN


/**
 * Context是一个基于std::map的容器，用于保存作用域Scope。
 * 作用域Scope同样是一个基于std::map的容器，用于保存Variable。
 * 变量Variable是由名称name和值values组成的一个键值对，name为字符串，values是一个可以含有多个值的列表，值可以是任意类型(std::any)。一个变量可以拥有多个值。
 * 
 * 当创建一个Context对象时，会默认创建一个根作用域，将其指针保存到成员root_中，同时current_也被设置为root_，表示当前作用域
 * 为根作用域。Context中的所有操作都是基于当前作用域(current_)进行。
 */
class Context{
public:
    using Unit                   = ValueUnit;
    using Pos                     = ScopePos;
    using InitValues           = std::initializer_list<Value>;

public:
    Context();
    Context(const Context &other) =delete;
    Context& operator=(const Context &other) =delete;

    Context&  makeScope(const String &name, bool entered=false);  /* 在当前作用域中创建一个它的子作用域。如果entered为true，那么创建该作用域后将直接进入 */
    Context&  enterScope(const String &name, bool created=false);   /* 进入当前作用域中的一个子作用域，如果created为true，那么在该作用域不存在时将创建 */ 
    Context&  leaveScope();                                                                   /* 离开当前作用域，返回到它的父作用域中 */
    Context&  cleanScope(const String &name);                                   /* 删除当前作用域的一个子作用域，同时也删除其中的所有变量及该子作用域的子作用域 */
    bool          probeScope(const String &name) const;                        /* 如果当前作用域中存在指定名称的子作用域，则返回true */
    bool          isRootScope() const;                                                         /* 如果当前作用域是根作用域，返回true */
    Pos            postion() const;                                                                 /* 获取当前作用域的Pos对象(对指针的包装) */
    void           setPostion(const Pos &pos);                                             /* 将当前作用域设置为pos所指定的作用域 */
    String        relation(const String &separator=" ") const;                    /* 获取从根作用域到当前作用域之间经过的每个作用域的名称组成的字符串，separator用于指定分隔符 */
    Querier      querier(bool absolute=false) const;                                /* 获取一个以当前作用域为起点的查询器，可查询作用域、变量的存在情况和获取多变量值 */
    Querier      querier(const String &name) const;                                /* 获取指定名称的Scope的查询器 */

    Context&   makeVariable(const String &name, ValueType type, const Value &value);      /* 在当前作用域创建一个变量，如果变量存在，则设置该变量的值和类型 */
    Context&   makeVariable(const String &name, ValueType type, InitValues values); /* 在当前作用域创建变量时一次性设置多个值 */
    Context&   cleanVariable(const String &name);                               /* 删除一个当前作用域中的变量 */  
    Unit            getValueUnit(const String &name) const;                       /* 获取一个当前作用域的变量的首个值及类型 */
    bool           probeVariable(const String &name) const;                     /* 如果当前作用域存在指定名称的变量，则返回true */
    Context&   extendValue(const String &name, const Value &value);          /* 向指定名称的变量中追加值 */    
    Context&   extendValues(const String &name, InitValues values);   /* 向指定名称的变量中追加多个值 */                                                       
    Context&   restart();                                                                /* 返回到根作用域，即设置当前作用域为根作用域 */
    void            clean();                                                                  /* 清除所有的作用域和变量，随后重新创建一个新的根作用域 */
    void            iterate(ContextSeeker &seeker) const;                 /* 从当前作用域开始，按DFS迭代其中的每个变量及每个子作用域 */
    const ScopeMetaData&  scopeMetaData() const noexcept;          /* 获取当前作用域的元数据 */

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
    void do_relation(ScopePtr scope, std::stringstream &stream, const String &separator) const;
};

inline UID Context::nextID() noexcept{
    return idCounter_++;
}

CSC_END
#endif