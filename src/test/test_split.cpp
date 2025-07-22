#include <iostream>
#include <vector>
#include <string>
#include "dbc/utility/utility.hpp"

using Dstring =std::string;
using namespace dbc;

void show(const decltype(splitPath("")) &names){
    std::cout << std::endl << ">>>>>>>>>>>>>>>>>>" << std::endl;
    for(auto &name : names){
        std::cout << name << std::endl;
    }
    std::cout << "<<<<<<<<<<<<<<<<<<" << std::endl; 
}

void show(const decltype(separate("")) &pair){
    std::cout << std::endl << ">>>>>>>>>>>>>>>>>>" << std::endl;
    std::cout << "prefix: " << std::get<0>(pair) << ", name: " << std::get<1>(pair) << std::endl;
    std::cout << "<<<<<<<<<<<<<<<<<<" << std::endl; 
}

int main(void){
    /*
    auto names = splitPath("/");
    show(names);
    names = splitPath("");
    show(names);
    names = splitPath("/a/b/c/");
    show(names);
    names = splitPath("/a/b/c");
    show(names);
    */

    auto pair = separate("/a/b/c/");
    show(pair);
    pair = separate("/a/b");
    show(pair);
    pair =separate("/a");
    show(pair);
    pair = separate("/");
    show(pair);
    pair = separate("");
    show(pair);
}