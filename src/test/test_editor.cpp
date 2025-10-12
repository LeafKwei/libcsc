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
        .makeVariable("u", {}, ValueType::Integer).extendValues("u", {98L, 203L, 494L})
        .makeVariable("z", {}, ValueType::Bool).extendValues("z", {true, false})
        .makeVariable("k", {4.5}, ValueType::Double)
    .leaveScope()
    .makeVariable("h", {39L, 89L}, ValueType::Integer)
    .makeScope("user")
        .makeVariable("name", {"Jerry"}, ValueType::String)
        .makeVariable("age", {10L}, ValueType::Integer)
    .leaveScope();

    std::cout << handler.toString() << std::endl;
}