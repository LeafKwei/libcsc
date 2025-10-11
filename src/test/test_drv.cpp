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
    std::cout <<  std::any_cast<String>(context.getValue("name").value) << std::endl;
    std::cout <<  std::any_cast<String>(context.getValue("age").value) << std::endl;
    std::cout <<  std::any_cast<String>(context.getValue("weight").value) << std::endl;
    context.leaveScope();
    std::cout <<  std::any_cast<String>(context.getValue("school").value) << std::endl;
}