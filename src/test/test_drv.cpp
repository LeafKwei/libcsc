#include <cstdio>
#include <iostream>
#include <fstream>
#include "csc/syntax/CmdDriver.hpp"
#include "csc/utility/utility.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    Context context(ScopeType::ListScope);
    CmdDriver drv;
    drv.drive(str, context);
    context.enterScope("custom").enterScope("tom");
    std::cout <<  valueToString(context.getValueUnit("name").value, ValueType::String) << std::endl;
    std::cout <<  valueToString(context.getValueUnit("age").value, ValueType::Integer) << std::endl;
    std::cout <<  valueToString(context.getValueUnit("weight").value, ValueType::Integer) << std::endl;
    context.leaveScope();
    std::cout <<  valueToString(context.getValueUnit("school").value, ValueType::String) << std::endl;
}