#include "csc/types.hpp"
#include "csc/syntax/Command.hpp"
#include "csc/syntax/CmdExecutor.hpp"
#include "csc/syntax/functions.hpp"
CSC_BEGIN

CmdExecutor::CmdExecutor(){
    m_root = std::make_shared<ContNode>();
    m_current = m_root;
}

bool CmdExecutor::exceed() const noexcept{
    return m_current -> nodes.size() == 0;
}

void CmdExecutor::pushToken(const Token &token){
    assert(m_current -> nodes.size() != 0);
    m_tokens.push_back(token);
    updateCurrentNode(operandTypeof(token));  //获取Token对应的操作数类型，然后更新m_current字段(即当前Node)
}

bool CmdExecutor::executable() const noexcept{
    return m_current -> commands.size() != 0;
}

bool CmdExecutor::execute(Context &context){
    auto &commands = m_current -> commands;
    assert(commands.size() > 0);

    /* 本例当前Node中的所有Command，通过runnable函数决定该Command是否可以处理当前的Token序列 */
    for(auto &cmd : commands){
        if(!cmd -> runnable(m_tokens)){
            continue;
        }

        /* 执行Command，随后清空Token列表和重设m_current为m_root  */
        cmd -> run(m_tokens, context);
        reset();
        return true;
    }

    return false;
}

void CmdExecutor::addCommand(CmdPtr cmd){
    if(cmd == nullptr || cmd -> sizeofTypes() == 0) throw CommandExcept("Invalid Command.");
    do_addCommand(m_root, cmd, 0);
}

/* 根据Command对象所需的OperandType找到或创建对应的Node，然后将Command对象保存到Node中 */
void CmdExecutor::do_addCommand(NodePtr node, CmdPtr cmd, Size_t opidx){
    /* 查找当前Node是否存在以opidx对应的OpType为key的Node，如果不存在则创建该Node */
    auto pos = node -> nodes.find(cmd ->opTypeAt(opidx));
    if(pos == node -> nodes.end()){
        auto pair = node -> nodes.insert({cmd ->opTypeAt(opidx), std::make_shared<ContNode>()});
        pos = pair.first;
    }

    /* 如果当前的OpType是最后一个，则保存Command到子Node */
    if(opidx == cmd -> sizeofTypes() - 1){
        pos -> second -> commands.push_back(cmd);
        return;
    }

    /* 如果OpType不是最后一个，则以子Node为基础继续递归 */
    do_addCommand(pos -> second, cmd, opidx + 1);
}

void CmdExecutor::updateCurrentNode(OperandType op){
    /* 查找当前Node中是否有匹配给定操作数类型的子Node，如果有则更新m_current字段为该Node，使得当前Node中的命令对象始终匹配Token列表 */
    auto pos = m_current -> nodes.find(op);
    if(pos == m_current -> nodes.end()){ 
        throw CommandExcept("Unexcepted token.");
    }

    m_current = pos -> second;
}

void CmdExecutor::reset(){
    m_tokens.clear();
    m_current = m_root;
}

CSC_END