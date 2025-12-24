#include<iostream>
#include "csc/utility/PathHelper.hpp"

using namespace csc;

int main(int argc, char *argv[]){
    PathHelper helper;

    helper.decompose(argv[1]);
    std::cout << "absolute: " << helper.absolute() << std::endl;
    std::cout << "rootonly: " << helper.rootonly() << std::endl;
    std::cout << "valid: " << helper.valid() << std::endl;
    std::cout << "complex: " << helper.complex() << std::endl;
    std::cout << "size: " << helper.size() << std::endl;
    std::cout << "dirname: " << helper.dirname() << std::endl;
    std::cout << "basename: " << helper.basename() << std::endl;
    std::cout << "compose10: " << helper.compose(10) << std::endl;
    std::cout << "compose2: " << helper.compose(2) << std::endl;
}