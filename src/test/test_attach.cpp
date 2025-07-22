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
    e = context.makeDomains("/a/b/c"); checke(e);
    e = context.enterDomain("/a/b/c"); checke(e);
    context.set("name", "tom");
    context.set("age", "18");

    if(context.existsDomain("/a/b/c")) std::cout << "found." << std::endl;
    Dcontext context2 = context.detachDomain("/a/b/c");
    std::cout << "context2 absolute: " << context2.absolutePath() << std::endl;
    if(context2.exists("name"))context2.set("name", "jerry");
    context2.set("home", "fandouhuayuan");

    if(!context.existsDomain("/a/b/c")){
        std::cout << "detached." << std::endl;
        std::cout << "We are at " << context.absolutePath() << " now." << std::endl;
    }

    context2.makeDomain("d");
    context2.enterDomain("d");
    context2.set("today", "20250722");

    std::cout << "absolute: "<< context2.absolutePath() << std::endl;
    std::cout << "today:" <<  context2.get("today") << std::endl;

    e = context.attachDomain("/a/b/c/", std::move(context2)); checke(e);
   context.enterDomain("/a/b/c");
    std::cout << context.get("name") << std::endl;
    e = context.enterDomain("/a/b/c/d"); checke(e);
    std::cout << context.get("today") << std::endl;
}