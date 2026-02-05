#ifndef CSC_SCOQUERIER_HPP
#define CSC_SCOQUERIER_HPP

#include <vector>
#include "csc/context/VarQuerier.hpp"
#include "csc/context/Scope.hpp"
CSC_BEGIN

/* ScoQuerier用于迭代指定Scope下的所有变量和子Scope  */
class ScoQuerier{
public:
    ScoQuerier(ScopePtr scop);
    ScoQuerier(ScopePos pos);

    bool         noscopes() const;              /* 此Scope不存在子Scope */
    bool         novariables() const;           /* 此Scope不存在变量 */
    String       name() const;                   /* 获取ScoQuerier当前所在的Scope名称 */
    Size_t       sizeofVariables() const;    /* 获取此Scope中的变量数量 */
    Size_t       sizeofScopes() const;       /* 获取此Scope中的直接子Scope的数量 */
    VarQuerier varquerier(int index=0) const; /* 获取指定位置的变量的查询器 */
    ScoQuerier scoquerier(int index=0) const; /* 获取指定位置的Scope的查询器 */

private:
    ScopeWptr scope_;
    ScopePtr lockScopePtr() const;
};

CSC_END
#endif