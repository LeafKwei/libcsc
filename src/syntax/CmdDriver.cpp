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
        throw CommandExcept("Bad Token: " + makeExceptMessage(script, Locator(script, lexer.index())));
    }

    while(!pool.empty()){
        if(executor_.reached()){
            throw CommandExcept("Unmatched command operands, keyseq: " + executor_.keyseq());
        }

        executor_.pushHolder(pool.nextHolder());
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

String CmdDriver::makeExceptMessage(const String &script, const Locator &locator){
    std::stringstream sstream;
    sstream << "row " << locator.row() << ", col " << locator.col() << ".";
    sstream << "text: " << script.substr(locator.index(), 32);
    return sstream.str();
}

CSC_END