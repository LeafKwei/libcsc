#include <iostream>
#include "dbc/core/Ditem.hpp"

using namespace dbc;

int main(void){
    std::cout << Ditem("true", ValueType::Bool).to<bool>() << std::endl;
    for(auto e : Ditem("true,false,true", ValueType::Bools).to<barray>()){
        std::cout << e << std::endl;
    }

    std::cout << "------------------------------" << std::endl;

    
}