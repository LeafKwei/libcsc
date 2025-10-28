#include "csc/types.hpp"
#include "csc/action/ActionMngr.hpp"
CSC_BEGIN

void ActionMngr::notifyActionBefore(CommandType type, const OperandList &operands, Context &context){
    do_notifyScopedAction(m_beforeActions, type, operands, context);
    do_notifyGlobalAction(m_beforeActions, type, operands, context);
    checkAndRemoveAction(m_beforeActions, type, context.scopeMetaData().id);
}

void ActionMngr::notifyActionAfter(CommandType type, const OperandList &operands, Context &context){
    do_notifyScopedAction(m_afterActions, type, operands, context);
    do_notifyGlobalAction(m_afterActions, type, operands, context);
    checkAndRemoveAction(m_afterActions, type, context.scopeMetaData().id);
}

/**
 * 将给定的runnable和run函数合并为Action对象后保存到action map中，scopeid将作为Action对象在map中的key，当触发notifyAction系列函数时，只有当context内的scopeID函数
 * 与作为key的scopeid一致时，才会尝试执行其中的Action。然后，当执行ExitScope命令时，ActionMngr会删除action map中退出的Scope的id对应的Action队列
 * 同时，当scope id为小于等于0的值时，将具有以下意义：
 *   0 --- Action为全局action，即无论Context中的scopeid是多少，都会尝试执行该Action
 */
void ActionMngr::addActionBefore(int scopeid, Action::FuncRunnable runnable, Action::FuncRun run){
    do_addAction(m_beforeActions, scopeid, runnable, run);
}

void ActionMngr::addActionAfter(int scopeid, Action::FuncRunnable runnable, Action::FuncRun run){
    do_addAction(m_afterActions, scopeid, runnable, run);
}

void ActionMngr::do_notifyScopedAction(ScopedActionMap &map, CommandType type, const OperandList &operands, Context &context){
    do_notifyAction(map, context.scopeMetaData().id, type, operands, context);
}

void ActionMngr::do_notifyGlobalAction(ScopedActionMap &map, CommandType type, const OperandList &operands, Context &context){
    do_notifyAction(map, 0, type, operands, context);
}

void ActionMngr::do_notifyAction(ScopedActionMap &map, int scopeid, CommandType type, const OperandList &operands, Context &context){
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

void ActionMngr::do_addAction(ScopedActionMap &map, int scopeid, const Action::FuncRunnable &runnable, const Action::FuncRun &run){
    auto actions = map.find(scopeid);
    if(actions == map.end()){         //如果scope id在action map中没有对应的Action队列，则创建一个空队列
        map.insert({scopeid, ActionQueue()});
        actions = map.find(scopeid);
    }

    actions -> second.push_back(Action{runnable, run});
}

void ActionMngr::checkAndRemoveAction(ScopedActionMap &map, CommandType type,  int scopeid){
    if(type != CommandType::ExitScope) return;
    if(map.find(scopeid) == map.end()) return;
    map.erase(scopeid);
}

CSC_END