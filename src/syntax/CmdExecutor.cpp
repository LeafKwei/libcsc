#include <cassert>
#include "csc/types.hpp"
#include "csc/syntax/Command.hpp"
#include "csc/syntax/CmdExecutor.hpp"
CSC_BEGIN


CmdExecutor::CmdExecutor() : m_maxKeySize(0){}

bool CmdExecutor::hasOperand() const noexcept{
    return m_operands.size() > 0;
}

bool CmdExecutor::reached() const noexcept{
    return m_keyseq.size() >= m_maxKeySize;
}

void CmdExecutor::pushToken(const Token &token){
    assert(m_keyseq.size() < m_maxKeySize);

    Operand op(token);
    if(op.typeofOperand() == OperandType::Unknown){
        throw CommandExcept("Unexcepted token: " + token.str);
    }

    m_operands.push_back(op);
    updateKeyseq(op);
}

bool CmdExecutor::executable() const{
    auto cmdListPtr = m_cmdListMap.find(m_keyseq);
    auto end = m_cmdListMap.end();

    return (cmdListPtr != end) && (cmdListPtr -> second.size() > 0);
}

bool CmdExecutor::execute(Context &context, ActionCtl &ctl){
    auto cmdListPtr = m_cmdListMap.find(m_keyseq);
    auto &cmdList = cmdListPtr -> second;
    auto end = m_cmdListMap.end();
    assert((cmdListPtr != end) && (cmdList.size() > 0));

    /* 遍历列表中所有Command，通过runnable函数决定该Command是否可以处理当前的Token序列 */
    for(auto &cmd : cmdList){
        if(!cmd -> runnable(m_operands)){
            continue;
        }

        /* 执行Command，随后清空Token列表和重设m_key  */
        cmd -> run(m_operands, context, ctl);
        reset();
        return true;
    }

    return false;
}

void CmdExecutor::addCommand(CmdPtr cmd){
    if(cmd == nullptr){
        throw CommandExcept("Pointer to command is a nullptr.");
    }

    /* 查找cmd的key是否已在map中存在对应的list对象，如果不存在则创建一个空list */
    auto key = cmd -> key();
    if(m_cmdListMap.find(key) == m_cmdListMap.end()){
        m_cmdListMap.insert({key, CmdList()});
    }

    /* 根据key获取list，将command添加到list中 */
    m_cmdListMap.at(key).push_back(cmd);
    m_maxKeySize = m_maxKeySize < key.size() ? key.size() : m_maxKeySize;
}

/* 获取Operand对应的key，追加到m_keyseq中，最终得到类型1_=_3形式的key。CmdExecutor根据该序列查找对应Command */
void CmdExecutor::updateKeyseq(const Operand &operand){
    const auto &key = operand.key();
    if(m_keyseq.size() == 0){
        m_keyseq.append(key);
        return;
    }

    m_keyseq.append("_").append(key);
}

void CmdExecutor::reset(){
    m_operands.clear();
    m_keyseq.clear();
}

CSC_END