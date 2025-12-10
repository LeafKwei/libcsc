#include<iostream>
#include "csc/lex/NumSect.hpp"

using namespace csc;

int main(int argc, char *argv[]){
    NumSect sect1(100, 200);
    NumSect sect2(300, 400);

    std::cout << sect1.contain(156) << std::endl;
    std::cout << sect1.lessThan(sect2) << std::endl;
    
    NumSect sect3(150, 300);
    std::cout << sect1.intersect(sect3) << std::endl;
    std::cout << sect1.intersect(sect2) << std::endl;

    sect2.setNum(500, 1000);
    auto newSect = sect1.merge(sect2);
    std::cout << newSect.left() << ", " << newSect.right() << std::endl;
}