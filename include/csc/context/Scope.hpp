#ifndef CSC_SCOPE_HPP
#define CSC_SCOPE_HPP

#include <memory>
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

class Scope{
public:
    virtual ~Scope() =default;
    virtual bool           insertVariable(const String &name, VariablePtr vp) =0;     //向作用域中插入一个Variable，并返回插入操作是否成功
    virtual VariablePtr findVariable(const String &name) =0;                                //按指定的名称寻找一个Variable
    virtual VariablePtr variable(int index) =0;                                                         //按指定的索引获取一个Variable
    virtual Size_t          size() const noexcept =0;                  //获取Scope中持有的Variable数量
    virtual String          name() const noexcept =0;              //获取Scope的名字
    virtual UID             id() const noexcept =0;                    //获取Scope的id
};

using ScopePtr   = std::shared_ptr<Scope>;
using ScopeWkr = std::weak_ptr<Scope>;

CSC_END
#endif