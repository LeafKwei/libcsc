#ifndef CSC_CMDDRIVER_HPP
#define CSC_CMDDRIVER_HPP

#include "csc/csc.hpp"
#include "csc/lex/Locator.hpp"
#include "csc/action/ActionHub.hpp"
#include "csc/syntax/CmdExecutor.hpp"

CSC_BEGIN

class CmdDriver{
public:
    CmdDriver();
    CmdDriver(const CmdDriver &other) =delete;
    CmdDriver& operator=(const CmdDriver &other) =delete;

    void drive(ConstStr script, Context &context);   /* 使用给定的Context对象开始对script进行解析执行 */

private:
    CmdExecutor m_executor;
    ActionHub     m_actionhub;

    void    installCommands();
    CscStr makeExceptMessage(ConstStr script, const Locator &locator);
};

CSC_END
#endif