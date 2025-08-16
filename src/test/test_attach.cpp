#include <iostream>
#include <cstdlib>
#include "dbc/core/Dcontext.hpp"
#include "dbc/utility/utility.hpp"

using namespace dbc;

int main(void){
    Dcontext context;
    context.makeDomains("/a/b/c"); 
    context.enterDomain("/a/b/c"); 
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

    context.attachDomain("/a/b/c/", std::move(context2)); 
    context.enterDomain("/a/b/c");
    std::cout << context.get("name") << std::endl;
    context.enterDomain("/a/b/c/d"); 
    std::cout << context.get("today") << std::endl;
}