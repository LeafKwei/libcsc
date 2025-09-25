#ifndef CSC_CMDDRIVER_HPP
#define CSC_CMDDRIVER_HPP

#include "csc/csc.hpp"
#include "csc/lex/Locator.hpp"
#include "csc/action/ActionHub.hpp"
#include "csc/syntax/CmdExecutor.hpp"

CSC_BEGIN

/* CmdDriver集成了CmdExecutor，负责将外部输入的配置文件内容(script)解析到Context中 */
class CmdDriver{
public:
    CmdDriver();
    CmdDriver(const CmdDriver &other) =delete;
    CmdDriver& operator=(const CmdDriver &other) =delete;

    void drive(crString script, Context &context);   /* 使用给定的Context对象开始对script进行解析执行 */

private:
    ActionHub     m_acthub;
    CmdExecutor m_executor;

    void    do_execute(Context &context);
    void    installCommands();
    String makeExceptMessage(crString script, const Locator &locator);
};

CSC_END
#endif