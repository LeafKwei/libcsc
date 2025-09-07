#ifndef CSC_SYNTAX_CMDS_HPP
#define CSC_SYNTAX_CMDS_HPP

#include <vector>
#include "csc/syntax/Command.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

class CommonCmd : public Command{
public:
    using InitOpTypes = std::initializer_list<OperandType>;
    using OpTypeList = std::vector<OperandType>;
    using ConstOpTypeList = const OpTypeList&;

public:
    CommonCmd() =default;
    CommonCmd(InitOpTypes types);
    
    int tokenNumber() override;
    Policy run(ConstTokenList &tokens, Context &context) override;

protected:
    virtual ConstOpTypeList typeList();
    virtual bool isThisType(ConstTokenList &tokens);
    virtual bool isLegalToken(ConstTokenList &tokens);

private:
    OpTypeList m_typeList;
};

class EnterScopeCmd : public CommonCmd{
public:
    EnterScopeCmd();
    Policy run(ConstTokenList &tokens, Context &context) override;
protected:
    bool isLegalToken(ConstTokenList &tokens) override;
};

class ExitScopeCmd : public CommonCmd{
public:
    ExitScopeCmd();
    Policy run(ConstTokenList &tokens, Context &context) override;
protected:
    bool isLegalToken(ConstTokenList &tokens) override;
};

class AssignCmd : public CommonCmd{
public:
    AssignCmd();
    Policy run(ConstTokenList &tokens, Context &context) override;
protected:
    bool isLegalToken(ConstTokenList &tokens) override;
};

class ArrayAssignCmd : public CommonCmd{
public:
    ArrayAssignCmd();
    Policy run(ConstTokenList &tokens, Context &context) override;
protected:
    bool isLegalToken(ConstTokenList &tokens) override;
};

CSC_END
#endif