#include <iostream>
#include "csc/context/Context.hpp"
using namespace csc;

int main(void){
    Context context;

    context.makeVariable("what", "Hello World!");
    context.makeScope("users", true)
        .makeScope("tom", true)
            .makeVariable("name", "tom", ValueType::String)
            .makeVariable("age", "18", ValueType::String)
            .leaveScope()
        .makeScope("jerry", true)
            .makeVariable("name", "jerry", ValueType::String)
            .makeVariable("age", "18", ValueType::String);

    context.restart();
    std::cout << context.getValue("what").str << std::endl;
    std::cout << context.enterScope("users").enterScope("tom").getValue("name").str << std::endl;

    context.restart();
    std::cout << context.enterScope("users").enterScope("jerry").getValue("age").str << std::endl;
    context.clean();
}