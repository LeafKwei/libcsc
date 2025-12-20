#ifndef CSC_CMDEXECUTOR_HPP
#define CSC_CMDEXECUTOR_HPP

#include <vector>
#include <memory>
#include <csc/alias.hpp>
#include "csc/csc.hpp"
#include "csc/lex/types.hpp"
#include "csc/syntax/types.hpp"
#include "csc/syntax/Operand.hpp"
#include "csc/syntax/Keyseq.hpp"
#include "csc/context/Context.hpp"
#include "csc/action/ActionMngr.hpp"
CSC_BEGIN

/**
 * CmdExecutor负责匹配和执行Command，其内部存在token序列的缓冲区，并提供了pushToken函数以便外部压入token。每当压入一个token，CmdExecutor
 * 会更新current_指针，使其指向匹配该token类型的Node
 * 
 * CmdExecutor也负责保存所有的Command对象，对于每个添加到其中的Command对象，CmdExecutor会根据该对象的OperandType列表，将其保存到一个合适
 * 的Node
 */
class CmdExecutor{
public:
    using CmdList = std::vector<Command>;
    using CmdListMap = std::map<String, CmdList>;
    using OperandList = std::vector<Operand>;

public:
    CmdExecutor();
    CmdExecutor(const CmdExecutor &other) =delete;
    CmdExecutor& operator=(const CmdExecutor &other) =delete;

    bool hasOperand() const noexcept;                                    /* 检查operands_中是否存在operand*/
    bool reached() const noexcept;                                          /* 检查key_的长度是否已达到了cmdListMap_中最长的key的长度 */
    void pushHolder(const TokenHolder &holder);                 /* 将指定TokenHolder转换为operand后压入operand列表，根据TokenHolder更新key_字段 */
    void pushHolder(TokenHolder &&holder);                        /* 将指定TokenHolder转换为operand后压入operand列表，根据TokenHolder更新key_字段 */
    bool executable() const;                                                     /* 检查当前的key_是否有对应的CmdList，即是否有匹配的可执行命令 */
    bool execute(Context &context, ActionMngr &mngr);      /* 使用当前的Token列表和给定的Context对象执行一条命令(即Command对象)，如果命令执行成功则返回true，如果操作数(而非类型)不匹配则返回false，此时应该继续pushToken以匹配后续命令 */

private:
    Size_t            maxKeySize_;
    Keyseq          keyseq_;
    OperandList  operands_;
    CmdListMap cmdListMap_;

    void installCmd();
    void addCommand(const String &key, CommandType type, CmdRun run);
    void addCommand(const String &key, CommandType type, CmdRunnable runnable, CmdRun run);
    void updateKeyseq(const Operand &operand);
    void reset();
};

CSC_END
#endif