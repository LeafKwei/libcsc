#include <iostream>
#include <fstream>
#include "csc/context/ctximpl/MapContext.hpp"
#include "csc/core/CscHandler.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    CscHandler<MapContext> handler;
    CscWriter writer = handler.writer();
    CscReader reader = handler.reader();
    writer.autoEnterOn().makeScope("custom")
        .makeVariable("u", ValueType::Integer).extendValues("u", 98, 203, 494)
        .makeVariable("z", ValueType::Bool).extendValues("z", true, false)
        .makeVariable("k", ValueType::Double, 4.5)
    .leaveScope()
    .makeVariable("h", ValueType::Integer, 39, 89)
    .makeScope("user")
        .makeVariable("name", ValueType::String, "Jerry", "Ami")
        .makeVariable("age",  ValueType::Integer, 10)
    .leaveScope();

     reader.enter("/");
    std::cout << reader.toString() << std::endl;
}