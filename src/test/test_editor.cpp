#include <iostream>
#include <fstream>
#include "csc/context/Context.hpp"
#include "csc/core/CscHandler.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    CscHandler<ScopeType::ListScope> handler;
    CscWriter writer = handler.writer();
    CscReader reader = handler.reader();
    writer.autoEnterOn().makeScope("custom")
        .makeVariable("u", 100).extendValues("u", 98, 203, 494)
        .makeVariable("z", true, false).extendValues("z", true, false)
        .makeVariable("k", 4.5, 4.6)
    .leaveScope()
    .makeVariable("h", 39, 89)
    .makeScope("user")
        .makeVariable("name", "Jerry", "Ami")
        .makeVariable("age", 10)
    .leaveScope();

     reader.enter("/");
    std::cout << reader.toString() << std::endl;
}