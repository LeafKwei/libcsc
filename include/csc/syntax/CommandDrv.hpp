#ifndef CSC_COMMANDDRV_HPP
#define CSC_COMMANDDRV_HPP

#include "csc/lex/Lexer.hpp"
#include "csc/syntax/cmds.hpp"
CSC_BEGIN

class CommandDrv{
public:
    using CommandPtr = std::shared_ptr<Command>;
    using CommandBranches = std::vector<CommandPtr>;

public:
    CommandDrv();
    void drive(const CscStr &script, Context &context);

private:
    size_t m_minTokenNum;
    size_t m_maxTokenNum;
    CommandBranches m_commands;

    void installCommands();
    void setTokenRange();
    CscStr makeMessage(const CscStr &tips, const Locator &locator);
};


CSC_END
#endif