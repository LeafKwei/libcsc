#include <iostream>
#include <fstream>
#include "csc/core/CscWalkerString.hpp"
#include "csc/context/Context.hpp"
#include "csc/syntax/CmdDriver.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    Context context(ScopeType::MapScope);
    CmdDriver drv;
    drv.drive(str, context);

    context.restart();
    Walker root = context.walker();
    CscWalkerString cws(root, true);
    std::cout << cws.localstr() << std::endl;

    std::cout << "====================" << std::endl;
    context.enterScope("custom");
    std::cout << cws.strfrom(context.walker(), false) << std::endl;
}