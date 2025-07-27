#include <iostream>
#include "dbc/lex/CharMngr.hpp"

using namespace dbc;

int main(void){
    const Dstring raw = "Hello Wolrd!";
    CharMngr mngr(raw);

    std::cout << mngr.pick() << std::endl;
    std::cout << mngr.pick() << std::endl;
    std::cout << mngr.count() << std::endl;
    std::cout << mngr.tryPick() << std::endl;
    std::cout << mngr.count() << std::endl;
    std::cout << mngr.charsoptor().startWith("") << std::endl;
}
