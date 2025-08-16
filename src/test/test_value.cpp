#include <iostream>
#include "dbc/core/Dvalue.hpp"

using namespace dbc;

int main(void){
    std::cout << Dvalue(ValueType::Null, "true").to<bool>() << std::endl;
    for(auto e : Dvalue(ValueType::Null, "true,false,true").to<barray>()){
        std::cout << e << std::endl;
    }

    std::cout << "------------------------------" << std::endl;

    
}