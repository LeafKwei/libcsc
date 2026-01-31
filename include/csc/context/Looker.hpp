#ifndef CSC_LOOKER_HPP
#define CSC_LOOKER_HPP

#include "csc/context/Scope.hpp"
CSC_BEGIN

/* Looker用于快速查找Context中是否存在指定名称的Scope */
class Looker{
public:
    Looker(ScopePtr scop);
    Looker(ScopePos pos);

    Looker& look(const String &name, bool asvar=false);   /* 检查当前Scope下是否存在指定名称的直接Scope或变量(asvar为true)，检查Scope的同时会进入该Scope，因此可链式调用此函数递进式检查。检查结果通过result函数获取 */
    bool        result() const noexcept;                                    /* 获取检查结果 */

private:
    bool result_;
    ScopeWptr scope_;
    ScopeWptr current_;

    ScopePtr lockScopePtr() const;
};

CSC_END
#endif