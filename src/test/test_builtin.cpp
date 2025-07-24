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

    e = context.enterDomain("/"); checke(e);
}