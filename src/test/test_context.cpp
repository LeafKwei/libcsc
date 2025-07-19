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



    std::cout << context.get("zhang san") << std::endl;
    std::cout << "Done...." << std::endl;
}