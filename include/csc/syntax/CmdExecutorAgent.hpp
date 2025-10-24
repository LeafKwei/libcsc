#ifndef CSC_CMDEXECUTORAGENT_HPP
#define CSC_CMDEXECUTORAGENT_HPP

#include "csc/syntax/CmdExecutor.hpp"
CSC_BEGIN

/* 向xxxexec_initialzer提供访问CmdExecutor内部私有函数的功能 */
class CmdExecutorAgent{
public:
    void addCommand(CmdExecutor &executor, CmdExecutor::CmdPtr cmdptr){ executor.addCommand(cmdptr); }
};

CSC_END
#endif