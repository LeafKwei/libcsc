#ifndef CSC_SYNTAX_CMDS_HPP
#define CSC_SYNTAX_CMDS_HPP

#include <vector>
#include "csc/syntax/Command.hpp"
#include "csc/utility/utility.hpp"
CSC_BEGIN

class CommonCmd : public Command{
public:
    CommonCmd() =default;
    CommonCmd(std::initializer_list<OperandType> types);
    
    int tokenNumber() override;
    Policy run(const std::vector<Token> &tokens, Context &context) override;

protected:
    virtual const std::vector<OperandType>& typeList();
    virtual bool isThisType(const std::vector<Token> &tokens);
    virtual bool isLegalToken(const std::vector<Token> &tokens);

private:
    std::vector<OperandType> m_typeList;
};

class EnterScopeCmd : public CommonCmd{
public:
    EnterScopeCmd();
    Policy run(const std::vector<Token> &tokens, Context &context) override;
protected:
    bool isLegalToken(const std::vector<Token> &tokens) override;
};

class ExitScopeCmd : public CommonCmd{
public:
    ExitScopeCmd();
    Policy run(const std::vector<Token> &tokens, Context &context) override;
protected:
    bool isLegalToken(const std::vector<Token> &tokens) override;
};

class AssignCmd : public CommonCmd{
public:
    AssignCmd();
    Policy run(const std::vector<Token> &tokens, Context &context) override;
protected:
    bool isLegalToken(const std::vector<Token> &tokens) override;
};

class ArrayAssignCmd : public CommonCmd{
public:
    ArrayAssignCmd();
    Policy run(const std::vector<Token> &tokens, Context &context) override;
protected:
    bool isLegalToken(const std::vector<Token> &tokens) override;
};

CSC_END
#endif