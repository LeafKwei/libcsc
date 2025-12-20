#include <cassert>
#include "csc/types.hpp"
#include "csc/syntax/Command.hpp"
#include "csc/syntax/commands.hpp"
#include "csc/syntax/CmdExecutor.hpp"
CSC_BEGIN


CmdExecutor::CmdExecutor() : maxKeySize_(0){
    installCmd();
}

bool CmdExecutor::hasOperand() const noexcept{
    return operands_.size() > 0;
}

bool CmdExecutor::reached() const noexcept{
    return (keyseq_.seq().size() > maxKeySize_);
}

void CmdExecutor::pushHolder(const TokenHolder &holder){
    Operand operand(holder);
    updateKeyseq(operand);
    operands_.push_back(holder);
}

void CmdExecutor::pushHolder(TokenHolder &&holder){
    Operand operand(std::move(holder));
    updateKeyseq(operand);
    operands_.push_back(std::move(operand));
}

bool CmdExecutor::executable() const{
    auto cmdListPtr = cmdListMap_.find(keyseq_.seq());
    auto end = cmdListMap_.end();

    return (cmdListPtr != end) && (cmdListPtr -> second.size() > 0);
}

bool CmdExecutor::execute(Context &context, ActionMngr &mngr){
    auto cmdListPtr = cmdListMap_.find(keyseq_.seq());
    auto &cmdList = cmdListPtr -> second;
    auto end = cmdListMap_.end();
    assert((cmdListPtr != end) && (cmdList.size() > 0));

    /* 遍历列表中所有Command，通过runnable函数决定该Command是否可以处理当前的Token序列 */
    for(auto &cmd : cmdList){
        if(!cmd.runnable(operands_)){
            continue;
        }

        /* 执行Command，在执行Command前/后将该Command的相关信息发送到ActionMngr，检查并执行合适的Action */
        mngr.notifyActionBefore(cmd.type, operands_, context);
        cmd.run(operands_, context, mngr);
        mngr.notifyActionAfter(cmd.type, operands_, context);

        /* 执行Command后，清空Operand列表，重设key_ */
        reset();
        return true;
    }

    return false;
}

void CmdExecutor::installCmd(){
    
}

void CmdExecutor::addCommand(const String &key, CommandType type, CmdRun run){
    addCommand(key, type, default_runnable, run);
}

void CmdExecutor::addCommand(const String &key, CommandType type, CmdRunnable runnable, CmdRun run){
    /* 查找cmd的key是否已在map中存在对应的list对象，如果不存在则创建一个空list */
    if(cmdListMap_.find(key) == cmdListMap_.end()){
        cmdListMap_.insert({key, CmdList()});
    }
    
    /* 根据key获取list，将command添加到list中，同时更新最长的key长度 */
    cmdListMap_.at(key).push_back(Command{
        key, 
        type, 
        runnable, 
        run
    });

    maxKeySize_ = maxKeySize_ < key.size() ? key.size() : maxKeySize_;
}

/* 获取Operand对应的key，追加到keyseq_中，最终得到类型1_=_3形式的key。CmdExecutor根据该序列查找对应Command */
void CmdExecutor::updateKeyseq(const Operand &operand){
    if(keyseq_.empty()){
        keyseq_.start(operand.key());
        return;
    }

    keyseq_.append(operand.key());
}

void CmdExecutor::reset(){
    operands_.clear();
    keyseq_.clear();
}

CSC_END