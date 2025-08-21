#include <cstdio>
#include <iostream>
#include <fstream>
#include "dbc/syntax/CommandDrv.hpp"
using namespace dbc;

int main(void){
    std::ifstream ifs("myconfig.dbc");
    Dstring str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    Context context;
    CommandDrv drv;
    drv.drive(str, context);
    context.enterScope("custom").enterScope("tom");
    std::cout << context.getVariable("name").value << std::endl;
    std::cout << context.getVariable("age").value << std::endl;
    std::cout << context.getVariable("weight").value << std::endl;
    context.leaveScope();
    std::cout << context.getVariable("school").value << std::endl;
}