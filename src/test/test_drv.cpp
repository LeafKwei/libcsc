#include <cstdio>
#include <iostream>
#include <fstream>
#include "csc/syntax/CmdDriver.hpp"
#include "csc/utility/utility.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    Context context;
    CmdDriver drv;
    drv.drive(str, context);
    context.enterScope("custom").enterScope("tom");
    std::cout <<  valueToString(context.getValue("name").value, ValueType::String) << std::endl;
    std::cout <<  valueToString(context.getValue("age").value, ValueType::Integer) << std::endl;
    std::cout <<  valueToString(context.getValue("weight").value, ValueType::Integer) << std::endl;
    context.leaveScope();
    std::cout <<  valueToString(context.getValue("school").value, ValueType::String) << std::endl;
}