#ifndef CSC_SCOPE_HPP
#define CSC_SCOPE_HPP

#include <type_traits>
#include <memory>
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

////////////////////////////////////////////////////////////////////////////////////////别名
class Scope;
using ScopePtr   = std::shared_ptr<Scope>;
using ScopeWkr = std::weak_ptr<Scope>;

////////////////////////////////////////////////////////////////////////////////////////辅助结构体
struct ScopeInf{
    UID id;
    String name;
};

struct ScopePos{
    ScopeWkr ptr;
};

////////////////////////////////////////////////////////////////////////////////////////枚举
enum class ScopeType{
    MapScope, ListScope
};

////////////////////////////////////////////////////////////////////////////////////////Scope定义
class Scope{
public:
    virtual ~Scope() =default;
    virtual bool insertScope(const String &name, ScopePtr sptr) =0;         //向作用域中插入一个Scope，返回插入操作是否成功
    virtual bool insertVariable(const String &name, VariablePtr vptr) =0;   //向作用域中插入一个Variable，返回插入操作是否成功
    virtual bool eraseScope(const String &name) =0;       //删除指定名称的Scope，返回删除操作是否成功
    virtual bool eraseVariable(const String &name) =0;     //删除指定名称的Variable，返回删除操作是否成功
    virtual ScopePtr   findScope(const String &name) =0;    //按指定的名称寻找一个直接子Scope
    virtual ScopePtr   scope(int index) =0;                             //按指定的索引获取一个直接子Scope
    virtual VariablePtr findVariable(const String &name) =0;  //按指定的名称寻找一个Variable
    virtual VariablePtr variable(int index) =0;                          //按指定的索引获取一个Variable
    virtual ScopePtr   parent() =0;                                         //获取此Scope的父Scope
    virtual void          setParent(ScopePtr parent) =0;          //设置父Scope         
    virtual Size_t        sizeofScopes() const noexcept =0;     //获取Scope中持有的直接子Scope数量
    virtual Size_t        sizeofVariables() const noexcept =0;   //获取Scope中持有的Variable数量
    virtual bool          noscopes() const noexcept =0;          //此Scope中是否没有任何直接子Scope
    virtual bool          novariables() const noexcept =0;      //此Scope中是否没有任何Variable
    virtual ScopeInf   scopeinf() const =0;                           //获取此Scope的基本信息
};

CSC_END
#endif