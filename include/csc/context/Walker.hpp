#ifndef CSC_WALKER_HPP
#define CSC_WALKER_HPP

#include <vector>
#include "csc/context/Querier.hpp"
#include "csc/context/Scope.hpp"
CSC_BEGIN

/* Walker用于迭代指定Scope下的所有变量和子Scope  */
class Walker{
public:
    using StringList = std::vector<String>;

public:
    Walker(ScopePtr scop);
    Walker(ScopePos pos);

    String       currentName() const;       /* 获取Walker当前所在的Scope名称 */
    StringList scopeNames() const;        /* 获取当前Scope下的所有直接子Scope的名称 */
    StringList variableNames() const;     /* 获取当前Scope中的所有变量名称 */
    Querier    querier(const String &name) const;      /* 获取指定名称的变量的查询器 */
    Walker     subwalker(const String &name) const; /* 获取指定名称的子Scope的漫步器 */

private:
    ScopeWptr scope_;
    ScopePtr lockScopePtr() const;
};

CSC_END
#endif