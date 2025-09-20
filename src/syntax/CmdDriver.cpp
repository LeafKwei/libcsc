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

    while(lexer.valid()){
        const auto &token = lexer.nextToken();
        if(token.type == TokenType::Aborted) break;
        if(token.type == TokenType::Unexcepted) throw CommandExcept("Unexcepted token at: " + makeExceptMessage(script, lexer.locator(-(token.buffer.size()))));
        
        if(m_executor.exceed()){
            throw CommandExcept("No command matches these tokens: " + makeExceptMessage(script, lexer.locator()));
        }

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