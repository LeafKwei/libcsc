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

class Context{
public:
    using Unit                   = ValueUnit;
    using Pos                     = ScopePos;
    using InitValues           = std::initializer_list<Value>;
    
public:
    virtual ~Context() =default;
    virtual Context&  makeScope(const String &name, bool entered=false) =0;  /* 在当前作用域中创建一个它的子作用域。如果entered为true，那么创建该作用域后将直接进入 */
    virtual Context&  enterScope(const String &name, bool created=false) =0;   /* 进入当前作用域中的一个子作用域，如果created为true，那么在该作用域不存在时将创建 */ 
    virtual Context&  leaveScope() =0;                                                                   /* 离开当前作用域，返回到它的父作用域中 */
    virtual Context&  cleanScope(const String &name) =0;                                   /* 删除当前作用域的一个子作用域，同时也删除其中的所有变量及该子作用域的子作用域 */
    virtual bool          hasScope(const String &name) const =0;                           /* 如果当前作用域中存在指定名称的子作用域，则返回true */
    virtual bool          isRootScope() const =0;                                                         /* 如果当前作用域是根作用域，返回true */
    virtual Pos            postion() const =0;                                                                 /* 获取当前作用域的Pos对象(对指针的包装) */
    virtual void           setPostion(const Pos &pos) =0;                                             /* 将当前作用域设置为pos所指定的作用域 */
    virtual Querier      querier(bool absolute=false) const =0;                                /* 获取一个以当前作用域为起点的查询器，可查询作用域、变量的存在情况和获取多变量值 */
    virtual Querier      querier(const String &name) const =0;                                /* 获取指定名称的Scope的查询器 */

    virtual Context&   makeVariable(const String &name, ValueType type, const Value &value) =0;      /* 在当前作用域创建一个变量，如果变量存在，则设置该变量的值和类型 */
    virtual Context&   makeVariable(const String &name, ValueType type, InitValues values) =0;          /* 在当前作用域创建变量时一次性设置多个值 */
    virtual Context&   cleanVariable(const String &name) =0;                                             /* 删除一个当前作用域中的变量 */  
    virtual Unit            getValueUnit(const String &name) const =0;                                   /* 获取一个当前作用域的变量的首个值及类型 */
    virtual bool           hasVariable(const String &name) const =0;                                     /* 如果当前作用域存在指定名称的变量，则返回true */
    virtual Context&   extendValue(const String &name, const Value &value) =0;            /* 向指定名称的变量中追加值 */    
    virtual Context&   extendValues(const String &name, InitValues values) =0;               /* 向指定名称的变量中追加多个值 */                                                       
    virtual Context&   restart() =0;                                                                /* 返回到根作用域，即设置当前作用域为根作用域 */
    virtual void            clean() =0;                                                                  /* 清除所有的作用域和变量，随后重新创建一个新的根作用域 */
    virtual void            iterate(ContextSeeker &seeker) const =0;                 /* 从当前作用域开始，按DFS迭代其中的每个变量及每个子作用域 */
    virtual const ScopeMetaData&  scopeMetaData() const noexcept =0;   /* 获取当前作用域的元数据 */
};

CSC_END
#endif