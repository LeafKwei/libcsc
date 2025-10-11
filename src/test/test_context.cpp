#include <iostream>
#include "csc/context/Context.hpp"
using namespace csc;

int main(void){
    Context context;

    context.makeVariable("what", "Hello World!", ValueType::String);
    context.makeScope("users", true)
        .makeScope("tom", true)
            .makeVariable("name", "tom", ValueType::String)
            .makeVariable("age", "18", ValueType::String)
            .leaveScope()
        .makeScope("jerry", true)
            .makeVariable("name", "jerry", ValueType::String)
            .makeVariable("age", "18", ValueType::String);

    context.restart();
    std::cout << std::any_cast<String>(context.getValue("what").value) << std::endl;
    std::cout <<  std::any_cast<String>(context.enterScope("users").enterScope("tom").getValue("name").value) << std::endl;

    context.restart();
    std::cout <<  std::any_cast<String>(context.enterScope("users").enterScope("jerry").getValue("age").value)<< std::endl;
    context.clean();

    context.makeScope("Kunkun", true)
        .makeVariable("music", "Chicken you are so beautiful.", ValueType::String);

    auto pos = context.postion();
    context.restart();
    std::cout << "Relation after restart: " << context.relation() << std::endl;
    context.setPostion(pos);
    std::cout << "Relation after setPostion: " << context.relation() << std::endl;
    std::cout << "Kunkun::music: " <<  std::any_cast<String>(context.getValue("music").value) << std::endl;
}