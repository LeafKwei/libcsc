#ifndef CSC_LOOKER_HPP
#define CSC_LOOKER_HPP

#include "csc/context/Scope.hpp"
CSC_BEGIN

/** 
 * Looker用于快速查找Context中是否存在指定名称的Scope 
 * 用户可以链式调用looksco和lookvar用于检查指定名称的Scope和变量是否存在，并在结尾调用done来获取检查结果。
 * 如果链式调用的过程中出现某个Scope或变量不存在的情况，则result被设置为false，同时后续的链式调用将不会生效
 */
class Looker{
public:
    Looker(ScopePtr scop);
    Looker(ScopePos pos);

    Looker& looksco(const String &name); /* 检查指定Scope是否存在，如果存在则更新current指针 */
    Looker& lookvar(const String &name); /* 检查指定变量是否存在 */
    bool done() const; /* 获取检查结果 */
    void reset(); /* 将current指针重设为scope指针，并重置result为true */

private:
    bool result_;
    ScopeWptr scope_;
    ScopeWptr current_;

    ScopePtr lockScopePtr() const;
};

CSC_END
#endif