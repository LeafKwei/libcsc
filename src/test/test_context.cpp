#include <iostream>
#include "csc/context/ctximpl/MapContext.hpp"
using namespace csc;

int main(void){
    MapContext context;

    context.makeVariable("what", ValueType::String, String("Hello World!"));
    context.makeScope("users", true)
        .makeScope("tom", true)
            .makeVariable("name", ValueType::String, String("tom"))
            .makeVariable("age", ValueType::String, "18")
            .leaveScope()
        .makeScope("jerry", true)
            .makeVariable("name", ValueType::String, String("jerry"))
            .makeVariable("age", ValueType::String, String("18"));

    context.restart();
    std::cout << std::any_cast<String>(context.getValueUnit("what").value) << std::endl;
    std::cout <<  std::any_cast<String>(context.enterScope("users").enterScope("tom").getValueUnit("name").value) << std::endl;

    context.restart();
    std::cout <<  std::any_cast<String>(context.enterScope("users").enterScope("jerry").getValueUnit("age").value)<< std::endl;
    context.clean();

    context.makeScope("Kunkun", true)
        .makeVariable("music", ValueType::String, String("Chicken you are so beautiful."));

    auto pos = context.postion();
    context.restart();
    context.setPostion(pos);
    std::cout << "Kunkun::music: " <<  std::any_cast<String>(context.getValueUnit("music").value) << std::endl;

    std::cout << "----------------------------" << std::endl;
    context.makeVariable("names", ValueType::String, {String("Tom"), String("Jerry"), String("Jimi"), String("Smith"), String("Amili")});
    Querier querier = context.querier();
    if(querier.hasVariable("names")){
        querier.captureVariable("names");
        for(auto i = 0; i < querier.querySize(); i++){
            std::cout << std::any_cast<String>(querier.queryValue(i).value) << std::endl;
        }
    }
}