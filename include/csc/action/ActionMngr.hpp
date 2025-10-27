#ifndef CSC_ACTIONMNGR_HPP
#define CSC_ACTIONMNGR_HPP

#include <deque>
#include <map>
#include "csc/action/ActionCtl.hpp"
CSC_BEGIN

class ActionMngr : public ActionCtl{
public:
    using ActionQueue         = std::deque<Action>;
    using ScopedActionMap = std::map<int, ActionQueue>;  /* int类型的key用于保存scope id */
    using OperandList           = std::vector<Operand>;

public:
    void notifyActionBefore(CommandType type, const OperandList &operands, Context &context);
    void notifyActionAfter(CommandType type, const OperandList &operands, Context &context);
    void addActionBefore(int scopeid, Action::FuncRunnable runnable, Action::FuncRun run) override; /* 添加Action到beforeActions队列 */
    void addActionAfter(int scopeid, Action::FuncRunnable runnable, Action::FuncRun run) override;   /* 添加Action到afterAction队列 */

private:
    ScopedActionMap m_beforeActions;
    ScopedActionMap m_afterActions;

    void do_notifyAction(ScopedActionMap &map, CommandType type, const OperandList &operands, Context &context);
    void do_addAction(ScopedActionMap &map, int scopeid, const Action::FuncRunnable &runnable, const Action::FuncRun &run);
    void checkAndRemoveAction(ScopedActionMap &map, CommandType type, int scopeid);
};

CSC_END
#endif