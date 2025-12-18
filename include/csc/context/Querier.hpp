#ifndef CSC_QUERIER_HPP
#define CSC_QUERIER_HPP

#include <map>
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
CSC_BEGIN

class Querier{
public:
    Querier(ScopePos spos);
    Querier(ScopePtr scope);

    bool tryEnter(const String &name);                    /* 尝试进入name指定的Scope内，进入失败是返回fasle */
    bool hasScope(const String &name) const;       /* 检查当前Scope下是否存在name指定的Scope */
    bool hasVariable(const String &name) const;    /* 检查当前Scope下是否存在name指定的Variable */
    ValueUnit directValue(const String &name) const;     /* 获取name指定的变量的首个值 */

    /* 以下函数需要执行captureVariable后调用 */
    Querier&  captureVariable(const String &name);        /* 保存name指定的Variable到var_中，以便后续对其中的值进行遍历 */
    ValueType queryType() const;                                      /* 获取var_中保存的变量的值的类型 */
    Size_t        querySize() const;                                       /* 获取var_中保存的变量的值的数量 */
    ValueUnit  queryValue(int index) const;                       /* var_中保存的变量在index位置的值 */

private:
    ScopeWkr     scope_;
    VariableWkr  var_;

    ScopePtr    lockScopePtr() const;
    VariablePtr lockVariablePtr() const;
};

CSC_END
#endif