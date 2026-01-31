#ifndef CSC_QUERIER_HPP
#define CSC_QUERIER_HPP

#include <map>
#include "csc/alias.hpp"
#include "csc/context/types.hpp"
#include "csc/context/Scope.hpp"
CSC_BEGIN

/* Querier用于查询指定变量的类型和每个值 */
class Querier{
public:
    Querier(VariablePtr varp);
    String        name() const;                                     /* 获取var_的变量名称 */
    ValueType type() const;                                      /* 获取var_中保存的变量的值的类型 */
    Size_t        size() const;                                       /* 获取var_中保存的变量的值的数量 */
    Value        value(int index=0) const;                   /* 获取var_中保存的变量在index位置的值 */
    ValueUnit valueunit(int index=0) const;           /* 获取var_中保存的变量在index位置的值及类型 */

private:
    VariableWkr  var_;
    VariablePtr lockVariablePtr() const;
};

CSC_END
#endif