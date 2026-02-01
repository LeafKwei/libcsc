#include <iostream>
#include <sstream>
#include "csc/lex/Lexer.hpp"
#include "csc/syntax/CmdDriver.hpp"
#include "csc/syntax/commands.hpp"
CSC_BEGIN
CmdDriver::CmdDriver(){
    
}

int CmdDriver::drive(const String &script, Context &context){
    Lexer lexer(script);
    TokenPool pool;
    auto cnt = 0;
    auto err = LxErrno::OK;

    while((err = lexer.readToken(pool)) == LxErrno::OK);
    if(err == LxErrno::Bad){
        throw CommandExcept("Bad Token: " + makeExceptMessage(script, lexer.index()));
    }

    while(!pool.empty()){
        /* 如果已经达到最长的命令seq的长度，则视为异常 */
        if(executor_.reached()){
            throw CommandExcept("Unmatched command operands, keyseq: " + executor_.keyseq());
        }

        /* 从Token池中获取一个TokenHolder，将其添加到CmdExecutor中并检查是否有可执行的命令，如有则执行  */
        auto holder = pool.nextHolder();
        executor_.pushHolder(holder);

        if(executor_.executable()){
            auto ok = executor_.execute(context, mngr_);
            cnt = (ok) ? cnt + 1 : cnt;
        }
    }

    /* 如果script解析完后存在多余未使用的operand则抛出异常 */
    if(!executor_.empty()){
        throw CommandExcept("Unused tokens in executor.");
    }

    return cnt;
}

String CmdDriver::makeExceptMessage(const String &script, Offset_t offset){
    std::stringstream sstream;
    Rowcol rc = locateFrom(script, offset);
    sstream << "row " << rc.first<< ", col " << rc.second<< ".";
    sstream << "text: " << script.substr(offset, 32);
    return sstream.str();
}

CSC_END