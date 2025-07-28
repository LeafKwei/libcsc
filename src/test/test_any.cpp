#include <iostream>
#include "dbc/lex/Locator.hpp"
using namespace dbc;

int main(void){
    Locator locator("Hello World\nYou are ok\n", 114514);
    std::cout << "Row: " <<locator.numberOfRow() << ", Col: " << locator.numberOfCol() << std::endl;
}