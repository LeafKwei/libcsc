#include <iostream>
#include "csc/context/Context.hpp"
using namespace csc;

int main(void){
    Context context;

    context.makeVariable("what", ValueType::String, "Hello World!");
    context.makeScope("users", true)
        .makeScope("tom", true)
            .makeVariable("name", ValueType::String, "tom")
            .makeVariable("age", ValueType::String, "18")
            .leaveScope()
        .makeScope("jerry", true)
            .makeVariable("name", ValueType::String, "jerry")
            .makeVariable("age", ValueType::String, "18");

    context.restart();
    std::cout << std::any_cast<String>(context.getValueUnit("what").value) << std::endl;
    std::cout <<  std::any_cast<String>(context.enterScope("users").enterScope("tom").getValueUnit("name").value) << std::endl;

    context.restart();
    std::cout <<  std::any_cast<String>(context.enterScope("users").enterScope("jerry").getValueUnit("age").value)<< std::endl;
    context.clean();

    context.makeScope("Kunkun", true)
        .makeVariable("music", ValueType::String, "Chicken you are so beautiful.");

    auto pos = context.postion();
    context.restart();
    std::cout << "Relation after restart: " << context.relation() << std::endl;
    context.setPostion(pos);
    std::cout << "Relation after setPostion: " << context.relation() << std::endl;
    std::cout << "Kunkun::music: " <<  std::any_cast<String>(context.getValueUnit("music").value) << std::endl;
}