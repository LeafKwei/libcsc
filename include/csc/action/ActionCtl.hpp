#ifndef CSC_ACTIONCTL_HPP
#define CSC_ACTIONCTL_HPP

#include <any>
#include "csc/alias.hpp"
#include "csc/action/types.hpp"
#include "csc/action/Action.hpp"
CSC_BEGIN

class ActionCtl{
public:
    virtual void addActionBefore(int scopeid, Action::ActRunnable runnable, Action::ActRun run) =0; /* 添加Action到beforeActions队列 */
    virtual void addActionAfter(int scopeid, Action::ActRunnable runnable, Action::ActRun run) =0;   /* 添加Action到afterAction队列 */
};

CSC_END
#endif