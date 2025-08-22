#include <iostream>
#include "dbc/context/Context.hpp"
using namespace dbc;

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
    std::cout << context.getVariable("what").value << std::endl;
    std::cout << context.enterScope("users").enterScope("tom").getVariable("name").value << std::endl;
    
    context.restart();
    std::cout << context.enterScope("users").enterScope("jerry").getVariable("age").value << std::endl;
    context.clean();
}