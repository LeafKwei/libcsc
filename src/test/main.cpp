#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::endl;

int main(void){
    string str{"Hello"};
    str = str + " World";

    std::cout << str << std::endl;

    return 0;
}