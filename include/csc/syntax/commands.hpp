#ifndef CSC_SYNTAX_COMMANDS_HPP
#define CSC_SYNTAX_COMMANDS_HPP

#include "csc/syntax/Command.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

class CommonCmd : public Command{
public:
    using InitTokens  = std::initializer_list<Token>;

public:
    CommonCmd() =default;
    CommonCmd(InitTokens types);
    crString key() override;

private:
    String m_key;

    void genKey(InitTokens tokens);
};

class EnterScopeCmd : public CommonCmd{
public:
    EnterScopeCmd();
    bool runnable(crOperandList operands) override;
    void run(crOperandList operands, Context &context, ActionCtl &ctl) override;
};

class ExitScopeCmd : public CommonCmd{
public:
    ExitScopeCmd();
    bool runnable(crOperandList operands) override;
    void run(crOperandList operands, Context &context, ActionCtl &ctl) override;
};

class AssignCmd : public CommonCmd{
public:
    AssignCmd();
    bool runnable(crOperandList operands) override;
    void run(crOperandList operands, Context &context, ActionCtl &ctl) override;
};

class ArrayAssignCmd : public CommonCmd{
public:
    ArrayAssignCmd();
    bool runnable(crOperandList operands) override;
    void run(crOperandList operands, Context &context, ActionCtl &ctl) override;
};

class ActionCmd : public CommonCmd{
public:
    ActionCmd();
    bool runnable(crOperandList operands) override;
    void run(crOperandList operands, Context &context, ActionCtl &ctl) override;

private:
    void run_genidx(ActionCtl &ctl, UID scopeid);
};

CSC_END
#endif