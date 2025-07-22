#include <iostream>
#include <cstdlib>
#include "dbc/core/Dcontext.hpp"
#include "dbc/utility/utility.hpp"

using namespace dbc;

void checke(Derror &e){
    if(e.type != ErrorType::OK){
        std::cout << "Error: " << e.message << std::endl;
        std::exit(0);
    }
}

int main(void){
    Dcontext context;
    decltype(context.enterDomain("")) e;

    e = context.makeDomain("/user"); checke(e);
    e = context.enterDomain("/user"); checke(e);
    context.set("zhang san", "19990804");
    e = context.dropDomain("/user"); checke(e);
    e = context.makeDomain("/user"); checke(e);
    e = context.makeDomain("/user/teen"); checke(e);
    e = context.makeDomain("/user/old"); checke(e);
    e = context.makeDomain("/user/old"); checke(e);
    e = context.makeDomains("/time/2025/01"); checke(e);
    e = context.enterDomain("/user/teen"); checke(e);
    context.set("Tom", "100");
    e = context.exitDomain(); checke(e);
    e = context.enterDomain("old"); checke(e);
    context.set("Jerry", "123");
    context.set("Jerry", "666");
    context.set("", "114514");
    context.enterDomain("/time/2025/01"); checke(e);
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