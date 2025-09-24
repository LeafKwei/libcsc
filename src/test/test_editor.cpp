#include <iostream>
#include <fstream>
#include "csc/core/CscHandler.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    CscHandler handler;
    CscEditor editor = handler.editor();
    editor.autoEnterOn().makeScope("custom")
        .makeVariable("u", {""}, ValueType::Integers).extendValues("u", {toString(98), toString(203), toString(494)})
        .makeVariable("z", {""}, ValueType::Bools).extendValues("z", {toString(true), toString(false)})
        .makeVariable("k", {toString(4.5)}, ValueType::Double)
    .leaveScope()
    .makeVariable("h", {"39", "89"}, ValueType::Integer)
    .makeScope("user")
        .makeVariable("name", {"Jerry"}, ValueType::String)
        .makeVariable("age", {toString(int(10))}, ValueType::Integer)
    .leaveScope();

    std::cout << handler.toString() << std::endl;
}