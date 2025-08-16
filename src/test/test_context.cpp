#include <iostream>
#include <cstdlib>
#include "dbc/core/Dcontext.hpp"
#include "dbc/utility/utility.hpp"

using namespace dbc;

int main(void){
    Dcontext context;

    context.makeDomain("/user");
    context.enterDomain("/user");
    context.set("zhang san", "19990804");
    context.dropDomain("/user");
    context.makeDomain("/user");
    context.makeDomain("/user/teen");
    context.makeDomain("/user/old");
    context.makeDomain("/user/old");
    context.makeDomains("/time/2025/01");
    context.enterDomain("/user/teen");
    context.set("Tom", "100");
    context.exitDomain();
    context.enterDomain("old");
    context.set("Jerry", "123");
    context.set("Jerry", "666");
    context.set("", "114514");
    context.enterDomain("/time/2025/01");
    context.set("today", "20250101");

    context.enterDomain("/user/teen");
    std::cout << "path: " << context.path() << ", absolute: " << context.absolutePath() <<  std::endl;
    std::cout << "value: " << context.get("Tom") << std::endl;
    context.enterDomain("/user/old");
    std::cout << "path: " << context.path() << ", absolute: " << context.absolutePath() << std::endl;
    std::cout << "value: " << context.get("Jerry") << std::endl;
    context.enterDomain("/user/old");
    std::cout << "path: " << context.path() << ", absolute: " << context.absolutePath() << std::endl;
    std::cout << "value: " << context.get("") << std::endl;
    context.enterDomain("/time/2025/01");
    std::cout << "path: " << context.path() << ", absolute: " << context.absolutePath() << std::endl;
    std::cout << "value: " << context.get("today") << std::endl;

    std::cout << "Done...." << std::endl;
}