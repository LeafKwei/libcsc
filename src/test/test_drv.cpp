#include <cstdio>
#include <iostream>
#include <fstream>
#include "csc/syntax/CommandDrv.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    CscStr str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    Context context;
    CommandDrv drv;
    drv.drive(str, context);
    context.enterScope("custom").enterScope("tom");
    std::cout << context.getValue("name") << std::endl;
    std::cout << context.getValue("age") << std::endl;
    std::cout << context.getValue("weight") << std::endl;
    context.leaveScope();
    std::cout << context.getValue("school") << std::endl;
}