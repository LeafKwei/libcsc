#include <iostream>
#include <fstream>
#include "csc/context/Context.hpp"
#include "csc/core/CscHandler.hpp"
#include "csc/utility/utility.hpp"
using namespace csc;

int main(int argc, char *argv[]){
    std::ifstream ifs1("myconfig.csc");
    String str1((std::istreambuf_iterator<char>(ifs1)), std::istreambuf_iterator<char>());

    std::ifstream ifs2("myconfig.2.csc");
    String str2((std::istreambuf_iterator<char>(ifs2)), std::istreambuf_iterator<char>());

    CscHandler<ScopeType::ListScope> handler;
    handler.handle(str1);
    std::cout << handler.reader().toString() << std::endl;
    
    std::cout << "==========================" << std::endl;
    handler.handle(str2);
    handler.reader().enter("/");
    std::cout << handler.reader().toString() << std::endl;

    return 0;
}