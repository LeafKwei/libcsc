#include <iostream>
#include <sstream>
#include "csc/syntax/CmdDriver.hpp"
#include "csc/syntax/commands.hpp"
CSC_BEGIN

CmdDriver::CmdDriver(){
    installCommands();
}

void CmdDriver::drive(const String &script, Context &context){

}

void CmdDriver::do_execute(Context &context){
    executor_.execute(context, mngr_);
}

void CmdDriver::installCommands(){
    
}

String CmdDriver::makeExceptMessage(const String &script, const Locator &locator){
    std::stringstream sstream;
    sstream << "row " << locator.row() << ", col " << locator.col() << ".";
    sstream << "text: " << script.substr(locator.index(), 32);
    return sstream.str();
}

CSC_END