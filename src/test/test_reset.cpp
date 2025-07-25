#include <iostream>
#include <cstdlib>
#include "dbc/core/Dcontext.hpp"
#include "dbc/utility/utility.hpp"

using namespace dbc;

int main(void){
    Dcontext context;
    context.makeDomains("/a/b/c/d");
    context.enterDomain("/a/b/c/d");
    context.set("name", "tom");

    std::cout << "==========Reset=========" << std::endl;
    context.resetContext();
    std::cout << "======================" << std::endl;

    context.makeDomains("/A/B/C/D");
    context.enterDomain("/A/B/C/D");
    context.set("name", "jerry");

    std::cout << context.get("name") << std::endl;
}