#ifndef CSC_SYNTAX_COMMANDS_HPP
#define CSC_SYNTAX_COMMANDS_HPP

#include "csc/syntax/Command.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

class CommonCmd : public Command{
public:
    using CmdType          = CommandType;
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
    CmdType type() override;
    bool         runnable(crOperandList operands) override;
    void         run(crOperandList operands, Context &context, ActionCtl &ctl) override;
};

class ExitScopeCmd : public CommonCmd{
public:
    ExitScopeCmd();
    CmdType type() override;
    bool        runnable(crOperandList operands) override;
    void         run(crOperandList operands, Context &context, ActionCtl &ctl) override;
};

class AssignCmd : public CommonCmd{
public:
    AssignCmd();
    CmdType  type() override;
    bool          runnable(crOperandList operands) override;
    void          run(crOperandList operands, Context &context, ActionCtl &ctl) override;
};

class ArrayAssignCmd : public CommonCmd{
public:
    ArrayAssignCmd();
    CmdType type() override;
    bool        runnable(crOperandList operands) override;
    void        run(crOperandList operands, Context &context, ActionCtl &ctl) override;
};

class ActionCmd : public CommonCmd{
public:
    ActionCmd();
    CmdType type() override;
    bool         runnable(crOperandList operands) override;
    void         run(crOperandList operands, Context &context, ActionCtl &ctl) override;

private:
    void run_genidx(ActionCtl &ctl, UID scopeid);
};

CSC_END
#endif