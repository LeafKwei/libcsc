#ifndef CSC_CMDCONTAINER_HPP
#define CSC_CMDCONTAINER_HPP

#include <iostream>
#include <csc/alias.hpp>
#include "csc/csc.hpp"
#include "csc/lex/types.hpp"
#include "csc/context/Context.hpp"
#include "csc/syntax/node.hpp"
CSC_BEGIN

class CmdExecutor{
public:
    using CmdPtr  = CommandPtr;
    using NodePtr = ContNodePtr;
    using TokenList = std::vector<Token>;
    using OpType = OperandType;

public:
    CmdExecutor();
    CmdExecutor(const CmdExecutor &other) =delete;
    CmdExecutor& operator=(const CmdExecutor &other) =delete;

    bool exceed() const noexcept;               /* 是否已到达最后一个Node，即无任何Node可匹配当前的Token列表，代表当前读入的Token序列出现了语法错误 */
    void pushToken(const Token &token);  /* 压入一个Token到Token列表，根据Token更新m_current字段 */
    bool executable() const noexcept;        /* 检查当前Node是否有可以执行的命令 */
    bool execute(Context &context);          /* 使用当前的Token列表和给定的Context对象执行一条命令(即Command对象)，如果命令执行成功则返回true，如果操作数(而非类型)不匹配则返回false，此时应该继续pushToken以匹配后续命令 */
    void addCommand(CmdPtr cmd);        /* 添加一个Command对象到Node树中 */

private:
    NodePtr m_root;
    NodePtr m_current;
    TokenList m_tokens;

    void       do_addCommand(NodePtr node, CmdPtr cmd, Size_t opidx);
    OpType  operandTypeof(const Token &token);
    void       updateCurrentNode(OperandType op);
};

CSC_END
#endif