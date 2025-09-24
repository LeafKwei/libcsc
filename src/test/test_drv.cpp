#include <cstdio>
#include <iostream>
#include <fstream>
#include "csc/syntax/CmdDriver.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    Context context;
    CmdDriver drv;
    drv.drive(str, context);
    context.enterScope("custom").enterScope("tom");
    std::cout << context.getValue("name").str << std::endl;
    std::cout << context.getValue("age").str << std::endl;
    std::cout << context.getValue("weight").str << std::endl;
    context.leaveScope();
    std::cout << context.getValue("school").str << std::endl;
}