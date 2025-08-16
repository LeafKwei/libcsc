#include <iostream>
#include <cstdlib>
#include "dbc/core/Dcontext.hpp"
#include "dbc/utility/utility.hpp"

using namespace dbc;

int main(void){
    Dcontext context;

    context.makeDomains("/a/b/c");
    context.enterDomain("a");
    context.set("name", "tom");
    context.set("height", "170");

    Dcontext context2;
    context2 = std::move(context);
    //context2 = std::move(context2);  //failed

    std::cout << "path: " << context2.path() << ", absolute: " << context2.absolutePath() <<  std::endl;
    std::cout << "value: " << context2.get("name") << std::endl;
    std::cout << "value: " << context2.get("height") << std::endl;
}