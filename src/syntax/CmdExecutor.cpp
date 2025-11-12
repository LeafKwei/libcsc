#include <cassert>
#include "csc/types.hpp"
#include "csc/syntax/Command.hpp"
#include "csc/syntax/CmdExecutor.hpp"
CSC_BEGIN


CmdExecutor::CmdExecutor() : maxKeySize_(0){}

bool CmdExecutor::hasOperand() const noexcept{
    return operands_.size() > 0;
}

bool CmdExecutor::reached() const noexcept{
    return keyseq_.size() >= maxKeySize_;
}

void CmdExecutor::pushToken(const Token &token){
    assert(keyseq_.size() < maxKeySize_);

    Operand op(token);
    if(op.typeofOperand() == OperandType::Unknown){
        throw CommandExcept("Unexcepted token: " + token.str);
    }

    operands_.push_back(op);
    updateKeyseq(op);
}

bool CmdExecutor::executable() const{
    auto cmdListPtr = cmdListMap_.find(keyseq_);
    auto end = cmdListMap_.end();

    return (cmdListPtr != end) && (cmdListPtr -> second.size() > 0);
}

bool CmdExecutor::execute(Context &context, ActionMngr &mngr){
    auto cmdListPtr = cmdListMap_.find(keyseq_);
    auto &cmdList = cmdListPtr -> second;
    auto end = cmdListMap_.end();
    assert((cmdListPtr != end) && (cmdList.size() > 0));

    /* 遍历列表中所有Command，通过runnable函数决定该Command是否可以处理当前的Token序列 */
    for(auto &cmd : cmdList){
        if(!cmd -> runnable(operands_)){
            continue;
        }

        /* 执行Command，在执行Command前/后将该Command的相关信息发送到ActionMngr，检查并执行适当的Action */
        mngr.notifyActionBefore(cmd -> type(), operands_, context);
        cmd -> run(operands_, context, mngr);
        mngr.notifyActionAfter(cmd -> type(), operands_, context);

        /* 执行Command后，清空Operand列表，重设m_key */
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
    if(cmdListMap_.find(key) == cmdListMap_.end()){
        cmdListMap_.insert({key, CmdList()});
    }

    /* 根据key获取list，将command添加到list中 */
    cmdListMap_.at(key).push_back(cmd);
    maxKeySize_ = maxKeySize_ < key.size() ? key.size() : maxKeySize_;
}

/* 获取Operand对应的key，追加到keyseq_中，最终得到类型1_=_3形式的key。CmdExecutor根据该序列查找对应Command */
void CmdExecutor::updateKeyseq(const Operand &operand){
    const auto &key = operand.key();
    if(keyseq_.size() == 0){
        keyseq_.append(key);
        return;
    }

    keyseq_.append("_").append(key);
}

void CmdExecutor::reset(){
    operands_.clear();
    keyseq_.clear();
}

CSC_END