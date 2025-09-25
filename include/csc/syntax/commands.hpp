#ifndef CSC_SYNTAX_COMMANDS_HPP
#define CSC_SYNTAX_COMMANDS_HPP

#ifndef CSC_SYNTAX_CMDS_HPP
#define CSC_SYNTAX_CMDS_HPP

#include <vector>
#include "csc/syntax/Command.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

class CommonCmd : public Command{
public:
    using InitOpTypes  = std::initializer_list<OperandType>;
    using OpTypeList   = std::vector<OperandType>;

public:
    CommonCmd() =default;
    CommonCmd(InitOpTypes types);
    
    Size_t     sizeofTypes() override;
    OpType  opTypeAt(int index) override;

private:
    OpTypeList m_types;
};

class EnterScopeCmd : public CommonCmd{
public:
    EnterScopeCmd();
    bool runnable(const TokenList &tokens) override;
    void run(const TokenList &tokens, Context &context, ActionCtl &ctl) override;
};

class ExitScopeCmd : public CommonCmd{
public:
    ExitScopeCmd();
    bool runnable(const TokenList &tokens) override;
    void run(const TokenList &tokens, Context &context, ActionCtl &ctl) override;
};

class AssignCmd : public CommonCmd{
public:
    AssignCmd();
    bool runnable(const TokenList &tokens) override;
    void run(const TokenList &tokens, Context &context, ActionCtl &ctl) override;
};

class ArrayAssignCmd : public CommonCmd{
public:
    ArrayAssignCmd();
    bool runnable(const TokenList &tokens) override;
    void run(const TokenList &tokens, Context &context, ActionCtl &ctl) override;
};

class ActionCmd : public CommonCmd{
public:
    ActionCmd();
    bool runnable(const TokenList &tokens) override;
    void run(const TokenList &tokens, Context &context, ActionCtl &ctl) override;

private:
    void run_genidx(ActionCtl &ctl, UID scopeid);
};

CSC_END
#endif

#endif