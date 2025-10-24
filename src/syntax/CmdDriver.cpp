#include <iostream>
#include <sstream>
#include "csc/syntax/CmdDriver.hpp"
#include "csc/syntax/commands.hpp"
#include "csc/lex/Lexer.hpp"
CSC_BEGIN

CmdDriver::CmdDriver(){
    installCommands();
}

void CmdDriver::drive(crString script, Context &context){
    Lexer lexer(script);

    /* 重复读入token并压入CmdExecutor中，并在具备匹配的命令时执行命令 */
    while(lexer.valid()){
        const auto &result = lexer.nextResult();
        if(result.hint == LexHint::Aborted) break;  //此语句必不可少，由于lexer会自动丢弃空白字符和注释，因此即使valid函数返回true，lexer也可能会因为后续字符全是空白字符或注释时返回Aborted
        if(result.token.type == TokenType::Unknown) throw CommandExcept("Unexcepted token at: " + makeExceptMessage(script, lexer.locator(-(result.token.str.size()))));
        
        /* 检查是否已达到最长的key长度，即已无Command可以适配当前的token序列 */
        if(m_executor.reached()){
            throw CommandExcept("Mismatched token sequence at nearby: " + makeExceptMessage(script, lexer.locator()));
        }

        /** 
         * 压入token，然后检查是否存在可执行的命令，如果有则执行。命令的执行可能会因操作数、操作符不匹配而失败，这种形式的失败不算作错误，而应该继续 
         * 向CmdExecutor压入token，直到最终成功执行命令、超出最长的key长度、到达文件末尾
         */
        m_executor.pushToken(result.token);
        if(m_executor.executable()){
            do_execute(context);
        }
    }

    /* 如果script解析完后存在多余未使用的operand则抛出异常 */
    if(m_executor.hasOperand()){
        throw CommandExcept("Unused tokens at end of file.");
    }
}

void CmdDriver::do_execute(Context &context){
    m_executor.execute(context, m_acthub);
}

void CmdDriver::installCommands(){
    stdexec_initializer(m_executor);
}

String CmdDriver::makeExceptMessage(crString script, const Locator &locator){
    std::stringstream sstream;
    sstream << "row " << locator.row() << ", col " << locator.col() << ".";
    sstream << "text: " << script.substr(locator.index(), 32);
    return sstream.str();
}

CSC_END