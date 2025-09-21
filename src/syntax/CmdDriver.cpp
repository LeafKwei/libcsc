#include <iostream>
#include <sstream>
#include "csc/syntax/CmdDriver.hpp"
#include "csc/syntax/commands.hpp"
#include "csc/lex/Lexer.hpp"
CSC_BEGIN

CmdDriver::CmdDriver(){
    installCommands();
}

void CmdDriver::drive(ConstStr script, Context &context){
    Lexer lexer(script);

    /* 重复读入token并压入CmdExecutor中，并在具备匹配的命令时执行命令 */
    while(lexer.valid()){
        const auto &token = lexer.nextToken();
        if(token.type == TokenType::Aborted) break;
        if(token.type == TokenType::Unexcepted) throw CommandExcept("Unexcepted token at: " + makeExceptMessage(script, lexer.locator(-(token.buffer.size()))));
        
        /* 检查是否已到的叶节点，即已无Command可以适配当前的token序列 */
        if(m_executor.exceed()){
            throw CommandExcept("No command matches these tokens: " + makeExceptMessage(script, lexer.locator()));
        }

        /** 
         * 压入token，然后检查是否存在可执行的命令，如果有则执行。命令的执行可能会因操作数、操作符不匹配而失败，这种形式的失败不算作错误，而应该继续 
         * 向CmdExecutor压入token，直到最终成功执行命令或到达叶节点
         */
        m_executor.pushToken(token);
        if(m_executor.executable()){
            m_executor.execute(context);
        }
    }
}

void CmdDriver::installCommands(){
    m_executor.addCommand(std::make_shared<EnterScopeCmd>());
    m_executor.addCommand(std::make_shared<ExitScopeCmd>());
    m_executor.addCommand(std::make_shared<AssignCmd>());
    m_executor.addCommand(std::make_shared<ArrayAssignCmd>());
}

CscStr CmdDriver::makeExceptMessage(ConstStr script, const Locator &locator){
    std::stringstream sstream;
    sstream << "row " << locator.row() << ", col " << locator.col() << ".";
    sstream << "text: " << script.substr(locator.index(), 32);
    return sstream.str();
}

CSC_END