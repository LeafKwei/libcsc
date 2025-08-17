#ifndef DBC_SYNTAX_CMDS_HPP
#define DBC_SYNTAX_CMDS_HPP

#include <vector>
#include "dbc/syntax/Command.hpp"
DBC_BEGIN

class CommonCmd : public Command{
public:
    CommonCmd() =default;
    CommonCmd(std::initializer_list<TokenType> types);
    
    int tokenNumber() override;
    Policy run(const std::vector<Token> &tokens, Dcontext &context) override;

protected:
    virtual const std::vector<TokenType>& typeList();
    virtual bool isThisType(const std::vector<Token> &tokens);
    virtual bool isLegalToken(const std::vector<Token> &tokens);

private:
    std::vector<TokenType> m_typeList;
};

class EnterDomainCmd : public CommonCmd{
public:
    EnterDomainCmd();
    Policy run(const std::vector<Token> &tokens, Dcontext &context) override;
protected:
    bool isLegalToken(const std::vector<Token> &tokens) override;
};

class ExitDomainCmd : public CommonCmd{
public:
    ExitDomainCmd();
    Policy run(const std::vector<Token> &tokens, Dcontext &context) override;
protected:
    bool isLegalToken(const std::vector<Token> &tokens) override;
};

class AssignCmd : public CommonCmd{
public:
    AssignCmd();
    Policy run(const std::vector<Token> &tokens, Dcontext &context) override;
protected:
    bool isLegalToken(const std::vector<Token> &tokens) override;
};

DBC_END
#endif