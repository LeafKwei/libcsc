#include<iostream>
#include "csc/core/PathHelper.hpp"

using namespace csc;

int main(int argc, char *argv[]){
    auto ptr = argc < 2 ? "" : argv[1];

    PathHelper helper(ptr);
    std::cout << helper.buildPath(helper.size());
}