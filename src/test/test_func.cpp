#include<iostream>
#include "csc/core/functions.hpp"
using namespace csc;

int main(int argc, char *argv[]){
    auto ptr = argc < 2 ? "" : argv[1];

    const auto &vec = splitPath(ptr);
    const auto &pair = detachName(ptr);

    std::cout << "----------------" << std::endl;
    for(auto &e : vec){
        std::cout << e << ", ";
    }
    std::cout << std::endl;

    std::cout << "----------------" << std::endl;
    std::cout << pair.first << ", " << pair.second;
}