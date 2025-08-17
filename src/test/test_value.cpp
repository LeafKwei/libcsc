#include <iostream>
#include "dbc/core/Dvalue.hpp"

using namespace dbc;

int main(void){
    std::cout << Dvalue("true").to<bool>() << std::endl;
    for(auto e : Dvalue("true,false,true").to<barray>()){
        std::cout << e << std::endl;
    }

    std::cout << "------------------------------" << std::endl;

    
}