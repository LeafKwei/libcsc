#ifndef CSC_SYNTAX_INITIALIZERS_HPP
#define CSC_SYNTAX_INITIALIZERS_HPP

#include <memory>
#include "csc/syntax/commands.hpp"
#include "csc/syntax/CmdExecutorAgent.hpp"
CSC_BEGIN

inline void stdexec_initializer(CmdExecutor &executor){
    CmdExecutorAgent agent;
    
    agent.addCommand(executor, std::make_shared<EnterScopeCmd>());
    agent.addCommand(executor, std::make_shared<ExitScopeCmd>());
    agent.addCommand(executor, std::make_shared<AssignCmd>());
    agent.addCommand(executor, std::make_shared<ArrayAssignCmd>());
    agent.addCommand(executor, std::make_shared<ActionCmd>());
}

CSC_END
#endif