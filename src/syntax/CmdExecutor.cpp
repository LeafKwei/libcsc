#include "csc/types.hpp"
#include "csc/syntax/Command.hpp"
#include "csc/syntax/CmdExecutor.hpp"
#include "csc/syntax/functions.hpp"
CSC_BEGIN


CmdExecutor::CmdExecutor() : m_maxKeySize(0){}

bool CmdExecutor::hasToken() const noexcept{
    return m_tokens.size() > 0;
}

bool CmdExecutor::exceed() const noexcept{
    return m_key.size() >= m_maxKeySize;
}

void CmdExecutor::pushToken(const Token &token){
    assert(m_key.size() < m_maxKeySize);
    m_tokens.push_back(token);
    updateKey(token);
}

bool CmdExecutor::executable() const{
    auto cmdListPtr = m_cmdListMap.find(m_key);
    auto end = m_cmdListMap.end();

    return (cmdListPtr != end) && (cmdListPtr -> second.size() > 0);
}

bool CmdExecutor::execute(Context &context, ActionCtl &ctl){
    auto cmdListPtr = m_cmdListMap.find(m_key);
    auto &cmdList = cmdListPtr -> second;
    auto end = m_cmdListMap.end();
    assert((cmdListPtr != end) && (cmdListPtr -> second.size() > 0));

    /* 遍历列表中所有Command，通过runnable函数决定该Command是否可以处理当前的Token序列 */
    for(auto &cmd : cmdList){
        if(!cmd -> runnable(m_tokens)){
            continue;
        }

        /* 执行Command，随后清空Token列表和重设m_key  */
        cmd -> run(m_tokens, context, ctl);
        reset();
        return true;
    }

    return false;
}

void CmdExecutor::addCommand(CmdPtr cmd){
    auto key = cmd -> key();

    if(m_cmdListMap.find(key) == m_cmdListMap.end()){
        m_cmdListMap.insert({key, CmdList()});
    }

    m_cmdListMap.at(key).push_back(cmd);
    m_maxKeySize = m_maxKeySize < key.size() ? key.size() : m_maxKeySize;
}

/* 将Token转换为key item后，追加到当前的m_key中，最终得到类型1_=_3形式的key */
void CmdExecutor::updateKey(const Token &token){
    const auto &ki = tokenToKeyItem(token);
    if(m_key.size() == 0){
        m_key.append(ki);
        return;
    }

    m_key.append("_").append(ki);
}

void CmdExecutor::reset(){
    m_tokens.clear();
    m_key.clear();
}

CSC_END