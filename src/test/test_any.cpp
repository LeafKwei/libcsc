#include <iostream>
#include "dbc/lex/CharMngr.hpp"
using namespace dbc;

int main(void){
    CharMngr mngr("Hello World!");

    std::cout << "-------------------" << std::endl;
    while(mngr.valid()){
        std::cout << mngr.forward() << std::endl;
    }

    std::cout << "-------------------" << std::endl;
    mngr.seek(CharMngr::End, 0);
    while(mngr.valid()){
        std::cout << mngr.backward() << std::endl;
    }

     std::cout << "-------------------" << std::endl;
     mngr.seek(CharMngr::Set, 0);
     int index = mngr.index();
     while(index < mngr.length()){
        std::cout << mngr.at(index) << std::endl;
        mngr.forward();
        index++;
     }

    std::cout << "-------------------" << std::endl;
    std::cout << "index: " << mngr.index() << ", length: " << mngr.length() << std::endl;
     mngr.seek(CharMngr::Current, -1);
     std::cout << "index: " << mngr.index() << ", length: " << mngr.length() << std::endl;
     if(mngr.valid()) std::cout << mngr.forward() << std::endl;
}