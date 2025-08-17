#include <iostream>
#include <sstream>
#include "dbc/syntax/CommandDrv.hpp"
DBC_BEGIN

CommandDrv::CommandDrv(){
    installCommands();
    setTokenRange();
}

void CommandDrv::drive(const Dstring &script, Dcontext &context){
    Lexer lexer(script);
    Policy policy;
    std::vector<Token> tokens;

    while(lexer.valid()){
        tokens.push_back(lexer.nextToken());

        if(tokens.size() > m_maxTokenNum){
            throw CommandExcept(makeMessage("Unexcepted command at ", lexer.locator()));
        }
        else if(tokens.size() < m_minTokenNum){
            continue;
        }

        for(auto &cmd : m_commands){
            policy = cmd -> run(tokens, context);
            if(policy == Policy::Accepted) break;
            if(policy == Policy::Missed) continue;
            if(policy == Policy::Bad) throw CommandExcept(makeMessage("Invalid command: ", lexer.locator()));
        }

        if(policy == Policy::Accepted){
            tokens.clear();
        }
    }

    if(tokens.size() != 0){
        throw CommandExcept(makeMessage("Unexcepted command at ", lexer.locator()));
    }
}

void CommandDrv::installCommands(){
    m_commands.push_back(std::make_shared<EnterDomainCmd>());
    m_commands.push_back(std::make_shared<ExitDomainCmd>());
    m_commands.push_back(std::make_shared<AssignCmd>());
}

void CommandDrv::setTokenRange(){
    int index = 1;
    int min = 0, max = 0;
    
    if(m_commands.size() == 0){
        m_minTokenNum = 0;
        m_maxTokenNum = 0;
        return;
    }

    min = m_commands[0] -> tokenNumber();
    max = m_commands[0] -> tokenNumber();

    for(; index < m_commands.size(); index++){
        auto num = m_commands[index] -> tokenNumber();
        min = num < min ? num : min;
        max = num > max ? num : max;
    }

    m_minTokenNum = min;
    m_maxTokenNum = max;
}

Dstring CommandDrv::makeMessage(const Dstring &tips, const Locator &locator){
    std::stringstream stream;
    stream 
        <<  tips 
        << "row: " << locator.row()
        << ", col: " << locator.col()
        << " near.";

    return stream.str();
}

DBC_END