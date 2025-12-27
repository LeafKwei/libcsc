#ifndef CSC_ACTIONMNGR_HPP
#define CSC_ACTIONMNGR_HPP

#include <deque>
#include <map>
#include "csc/action/ActionCtl.hpp"
CSC_BEGIN

template<typename Scp>
class ActionMngr : public ActionCtl<Scp>{
public:
    using ActionQueue         = std::deque<Action<Scp>>;
    using ScopedActionMap = std::map<int, ActionQueue>;  /* int类型的key用于保存scope id */
    using OperandList           = std::vector<Operand>;

public:
    void notifyActionBefore(CommandType type, OperandList &operands, Context<Scp> &context);
    void notifyActionAfter(CommandType type, OperandList &operands, Context<Scp> &context);
    void addActionBefore(int scopeid, ActionCtl<Scp>::ActRunnable runnable, ActionCtl<Scp>::ActRun run) override; /* 添加Action到beforeActions队列 */
    void addActionAfter(int scopeid, ActionCtl<Scp>::ActRunnable runnable, ActionCtl<Scp>::ActRun run) override;   /* 添加Action到afterAction队列 */

private:
    ScopedActionMap beforeActions_;
    ScopedActionMap afterActions_;

    void do_notifyScopedAction(ScopedActionMap &map, CommandType type, OperandList &operands, Context<Scp> &context);
    void do_notifyGlobalAction(ScopedActionMap &map, CommandType type, OperandList &operands, Context<Scp> &context);
    void do_notifyAction(ScopedActionMap &map, int scopeid, CommandType type, OperandList &operands, Context<Scp> &context);
    void do_addAction(ScopedActionMap &map, int scopeid, ActionCtl<Scp>::ActRunnable &runnable, ActionCtl<Scp>::ActRun &run);
    void checkAndRemoveAction(ScopedActionMap &map, CommandType type, int scopeid);
};

template<typename Scp>
inline void ActionMngr<Scp>::notifyActionBefore(CommandType type, OperandList &operands, Context<Scp> &context){
    do_notifyScopedAction(beforeActions_, type, operands, context);
    do_notifyGlobalAction(beforeActions_, type, operands, context);
    checkAndRemoveAction(beforeActions_, type, context.scopeMetaData().id);
}

template<typename Scp>
inline void ActionMngr<Scp>::notifyActionAfter(CommandType type, OperandList &operands, Context<Scp> &context){
    do_notifyScopedAction(afterActions_, type, operands, context);
    do_notifyGlobalAction(afterActions_, type, operands, context);
    checkAndRemoveAction(afterActions_, type, context.scopeMetaData().id);
}

/**
 * 将给定的runnable和run函数合并为Action对象后保存到action map中，scopeid将作为Action对象在map中的key，当触发notifyAction系列函数时，只有当context内的scopeID函数
 * 与作为key的scopeid一致时，才会尝试执行其中的Action。然后，当执行ExitScope命令时，ActionMngr<Scp>会删除action map中退出的Scope的id对应的Action队列
 * 同时，当scope id为小于等于0的值时，将具有以下意义：
 *   0 --- Action为全局action，即无论Context中的scopeid是多少，都会尝试执行该Action
 */
template<typename Scp>
inline void ActionMngr<Scp>::addActionBefore(int scopeid, typename Action<Scp>::ActRunnable runnable, typename Action<Scp>::ActRun run){
    do_addAction(beforeActions_, scopeid, runnable, run);
}

template<typename Scp>
inline void ActionMngr<Scp>::addActionAfter(int scopeid, Action::ActRunnable runnable, Action::ActRun run){
    do_addAction(afterActions_, scopeid, runnable, run);
}

template<typename Scp>
inline void ActionMngr<Scp>::do_notifyScopedAction(ScopedActionMap &map, CommandType type, OperandList &operands, Context<Scp> &context){
    do_notifyAction(map, context.scopeMetaData().id, type, operands, context);
}

template<typename Scp>
inline void ActionMngr<Scp>::do_notifyGlobalAction(ScopedActionMap &map, CommandType type, OperandList &operands, Context<Scp> &context){
    do_notifyAction(map, 0, type, operands, context);
}

template<typename Scp>
inline void ActionMngr<Scp>::do_notifyAction(ScopedActionMap &map, int scopeid, CommandType type, OperandList &operands, Context<Scp> &context){
    /* 根据Scope的id找到对应的Action队列*/
    auto actions = map.find(scopeid);
    if(actions == map.end()){
        return;
    }

    /* 依次匹配队列中的每个Action，并尝试执行 */
    auto &queue = actions -> second;
    for(auto &action : queue){
        if(action.runnable(type, operands, context)){
            action.run(type, operands, context);
        }
    }
}

template<typename Scp>
inline void ActionMngr<Scp>::do_addAction(ScopedActionMap &map, int scopeid, Action::ActRunnable &runnable, Action::ActRun &run){
    auto actions = map.find(scopeid);
    if(actions == map.end()){         //如果scope id在action map中没有对应的Action队列，则创建一个空队列
        map.insert({scopeid, ActionQueue()});
        actions = map.find(scopeid);
    }

    actions -> second.push_back(Action{runnable, run});
}

template<typename Scp>
inline void ActionMngr<Scp>::checkAndRemoveAction(ScopedActionMap &map, CommandType type,  int scopeid){
    if(type != CommandType::ExitScope) return;
    if(map.find(scopeid) == map.end()) return;
    map.erase(scopeid);
}

CSC_END
#endif