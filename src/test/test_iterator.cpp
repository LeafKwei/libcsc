#include <iostream>
#include <fstream>
#include "csc/context/ctximpl/MapContext.hpp"
#include "csc/core/CscStrSeeker.hpp"
#include "csc/syntax/CmdDriver.hpp"
using namespace csc;

int main(void){
    std::ifstream ifs("myconfig.csc");
    String str((std::istreambuf_iterator<char>(ifs)), std::istreambuf_iterator<char>());

    MapContext context;
    CmdDriver drv;
    CscStrSeeker seeker;
    drv.drive(str, context);

    context.iterate(seeker);
    std::cout << seeker.toString() << std::endl;

    CscStrSeeker seeker2;
    context.enterScope("custom");
    context.iterate(seeker2);
    std::cout << seeker2.toString() << std::endl;
}