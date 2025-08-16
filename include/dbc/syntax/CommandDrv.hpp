#ifndef DBC_COMMANDDRV_HPP
#define DBC_COMMANDDRV_HPP

#include "dbc/lex/Lexer.hpp"
#include "dbc/syntax/cmds.hpp"
DBC_BEGIN

class CommandDrv{
public:
    CommandDrv();
    void drive(const Dstring &script, Dcontext &context);

private:
    int m_minTokenNum;
    int m_maxTokenNum;
    CommandBranches m_commands;

    void installCommands();
    void setTokenRange();
    Dstring makeMessage(const Dstring &tips, const Locator &locator);
};


DBC_END
#endif