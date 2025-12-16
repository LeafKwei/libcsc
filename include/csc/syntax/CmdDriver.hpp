#ifndef CSC_CMDDRIVER_HPP
#define CSC_CMDDRIVER_HPP

#include "csc/csc.hpp"
#include "csc/lex/Locator.hpp"
#include "csc/syntax/CmdExecutor.hpp"

CSC_BEGIN

/* CmdDriver集成了CmdExecutor，负责将外部输入的配置文件内容(script)解析到Context中 */
class CmdDriver{
public:
    CmdDriver();
    CmdDriver(const CmdDriver &other) =delete;
    CmdDriver& operator=(const CmdDriver &other) =delete;

    void drive(const String &script, Context &context);   /* 使用给定的Context对象开始对script进行解析执行 */

private:
    CmdExecutor executor_;
    ActionMngr   mngr_;

    void    do_execute(Context &context);
    void    installCommands();
    String makeExceptMessage(const String &script, const Locator &locator);
};

CSC_END
#endif